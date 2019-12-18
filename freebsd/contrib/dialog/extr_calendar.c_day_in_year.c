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
 scalar_t__ days_per_month (int,int) ; 

__attribute__((used)) static int
day_in_year(int year, int month, int day)
{
    int result = day;
    while (--month >= 1)
	result += days_per_month(year, month);
    return result;
}