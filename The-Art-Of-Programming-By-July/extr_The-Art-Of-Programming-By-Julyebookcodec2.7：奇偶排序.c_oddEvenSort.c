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
 scalar_t__ isOddNumber (int) ; 
 int /*<<< orphan*/  swap (int,int) ; 

void oddEvenSort(int *pData, unsigned int length)
{
	if (pData == NULL || length == 0)
		return;

	int *pBegin = pData;
	int *pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		//如果pBegin指针指向的是奇数，正常，向后移
		if (isOddNumber(*pBegin))
		{
			pBegin++;
		}
		//如果pEnd指针指向的是偶数，正常，向前移
		else if (!isOddNumber(*pEnd))
		{
			pEnd--;
		}
		else
		{
			//否则都不正常，交换
			swap(*pBegin, *pEnd);
		}
	}
}