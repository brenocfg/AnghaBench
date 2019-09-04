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

int FindOneNumber(int* a, int length)
{
	int candidate = a[0];
	int nTimes, i;
	for (i = nTimes = 0; i < length; i++)
	{
		if (candidate == a[i])
			nTimes++;
		else 
			nTimes--;
		if (nTimes == 0)
		{
			candidate = a[i];
			nTimes = 1;
		}
	}
	return candidate;
}