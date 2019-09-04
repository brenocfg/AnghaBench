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

void reverse(int *a, int from, int to)
{
	int t;
	for (; from < to; ++from, --to)
	{
		t = a[from];
		a[from] = a[to];
		a[to] = t;
	}
}