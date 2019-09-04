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
 int* nullptr ; 

int maxSubArray(int* a, int n)
{
	if (a == nullptr || n == 0)
		return 0;

	int currSum = 0;
	int maxSum = a[0];       //全负情况，返回最大数

	for (int j = 0; j < n; j++)
	{
		currSum = (a[j] > currSum + a[j]) ? a[j] : currSum + a[j];
		maxSum = (maxSum > currSum) ? maxSum : currSum;

	}
	return maxSum;
}