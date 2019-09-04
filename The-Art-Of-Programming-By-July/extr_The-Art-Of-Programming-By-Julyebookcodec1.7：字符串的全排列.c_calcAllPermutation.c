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
 char cout ; 
 char endl ; 
 int /*<<< orphan*/  reverse (char*,char*) ; 
 int /*<<< orphan*/  swap (char,char) ; 

void calcAllPermutation(char* perm, int num)
{
	if (num < 1)
		return;

	for (int i = 0; i < num; i++)
	{
		cout << perm[i];
	}
	cout << endl;

	while (true)
	{
		int i;
		for (i = num - 2; i >= 0; --i)
		{
			if (perm[i] < perm[i + 1])
				break;
		}
		if (i < 0)
		{
			break;  // 已经找到所有排列
		}
		int k;
		for (k = num - 1; k > i; --k)
		{
			if (perm[k] > perm[i])
				break;
		}
		swap(perm[i], perm[k]);
		//reverse 左闭右开
		reverse(perm + i + 1, perm + num);
		for (int i = 0; i < num; i++)
		{
			cout <<perm[i];
		}
		cout << endl;
	}
}