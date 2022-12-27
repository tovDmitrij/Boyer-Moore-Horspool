#include <iostream>
#include <list>
#include <chrono>
#include "StopSymbols.h"
using namespace std;

/// <summary>
/// Нахождение всех вхождений подстроки в строке (алгоритм Бойера-Мура-Хорспула)
/// </summary>
/// <param name="substr">Подстрока (образ)</param>
/// <param name="str">Строка</param>
/// <returns>Список позиций</returns>
list<int> BMH(const char* substr, const char* str) {
	list<int> result;
	StopSymbols* stopSymbols = new StopSymbols();
	stopSymbols->Init(substr);
	int strLength = strlen(str);
	int substrLength = strlen(substr);

	int currentPosition = 0;
	while (currentPosition <= strLength - substrLength)
	{
		int substrIndex = substrLength - 1;
		while (substrIndex >= 0 && substr[substrIndex] == str[currentPosition + substrIndex])
		{
			substrIndex--;
		}

		switch (substrIndex < 0)
		{
		case true:
			result.push_back(currentPosition);
			currentPosition += substrLength;
			break;
		case false:
			currentPosition += max(1, stopSymbols->Get(str[currentPosition]));
			break;
		}
	}

	delete stopSymbols;
	return result;
}

/// <summary>
/// Вывод списка на консоль
/// </summary>
/// <param name="valueList">Список</param>
template<typename T> void Print(list<T> valueList) {
	for (T current : valueList) {
		cout << current << " ";
	}
	cout << endl;
}

/// <summary>
/// Вывод объекта на консоль
/// </summary>
/// <param name="value">Объект</param>
template<typename T> void Print(T value) {
	cout << value << endl;
}

//#define _BM_
int main()
{
	setlocale(LC_ALL, "Russian");

	const char* obraz = "dolor";
	const char* str = "Ndoloreque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adidolorpdolorisci velitdolor";
	//					dolor							 dolor			    dolor							dolor dolor			 dolor
	//					1								 34				    53								85	  91			 106
	Print(obraz);
	Print(str);
	Print(BMH(obraz, str));



#pragma region Генерация исходных данных (строка и подстрока)

	const int N = 8192;
	const int M = 64;
	const int alphaBetSize = 'и' - 'a' + 1;
	char* randStr = new char[N + 1] {0};
	char* randObraz = new char[M + 1] {0};

	for (int i = 0; i < N; i++) {
		randStr[i] = rand() % alphaBetSize + 'a';
		srand(time(NULL) * i);
	}
	for (int i = 0; i < M; i++) {
		randObraz[i] = rand() % alphaBetSize + 'a';
		srand(time(NULL) * i);
	}

	Print("\n\tСтрока\n");
	Print(randStr);
	Print("\n\tОбраз\n");
	Print(randObraz);

#pragma endregion



#pragma region Исследование сложности string.find() и BMH()

	auto start = chrono::steady_clock::now();

#ifdef _BM_

	list<int> result = BMHZT(randObraz, randStr);

#else

	list<int> result;
	string t = randObraz;
	string T = randStr;
	int off = T.find(t, 0);

	while (off != -1)
	{
		result.push_back(off);
		off = T.find(t, off + 1);
	}

#endif

	auto stop = chrono::steady_clock::now();
	Print("\n\tИТОГИ ТЕСТИРОВАНИЯ (мс):\n");
	Print(chrono::duration_cast<chrono::microseconds>(stop - start).count());

#pragma endregion



}