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
 int MAX_DAYS ; 

__attribute__((used)) static int
day_of_week(int y, int m, int d)
{
    static int t[] =
    {
	0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4
    };
    y -= (m < 3);
    return (6 + (y + (y / 4) - (y / 100) + (y / 400) + t[m - 1] + d)) % MAX_DAYS;
}