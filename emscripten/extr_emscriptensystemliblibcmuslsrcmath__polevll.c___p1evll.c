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

long double __p1evll(long double x, const long double *P, int n)
{
	long double y;

	n -= 1;
	y = x + *P++;
	do {
		y = y * x + *P++;
	} while (--n);

	return y;
}