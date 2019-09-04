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
 int /*<<< orphan*/  perfect_shuffle3 (int*,int) ; 

void shuffle(int *a, int n)
{
	int i, t, n2 = n * 2;
	perfect_shuffle3(a, n);
	for (i = 2; i <= n2; i += 2)
	{
		t = a[i - 1];
		a[i - 1] = a[i];
		a[i] = t;
	}
}