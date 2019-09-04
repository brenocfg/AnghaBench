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
 int N ; 

void pefect_shuffle1(int *a, int n)
{
	int n2 = n * 2, i, b[N];
	for (i = 1; i <= n2; ++i)
	{
		b[(i * 2) % (n2 + 1)] = a[i];
	}
	for (i = 1; i <= n2; ++i)
	{
		a[i] = b[i];
	}
}