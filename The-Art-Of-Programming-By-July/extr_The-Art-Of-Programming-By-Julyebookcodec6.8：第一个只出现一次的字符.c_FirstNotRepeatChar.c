#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

char FirstNotRepeatChar(char* pString)
{
	if (!pString)
		return '\0';

	const int tableSize = 256;
	int hashTable[tableSize] = {0}; //存入数组，并初始化为0

	char* pHashKey = pString;
	while (*(pHashKey) != '\0')
		hashTable[*(pHashKey++)]++;

	while (*pString != '\0')
	{
		if (hashTable[*pString] == 1)
			return *pString;

		pString++;
	}
	return '\0';  //没有找到满足条件的字符，退出
}