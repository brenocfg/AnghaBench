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

__attribute__((used)) static int
month_length(int year, int month)
{
	static const int base_month_length[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	int x;

	x = base_month_length[month - 1];
	if (month == 2 && year % 4 == 0
		&& (year % 100 != 0 || year % 400 == 0))
	{
		x ++;
	}
	return x;
}