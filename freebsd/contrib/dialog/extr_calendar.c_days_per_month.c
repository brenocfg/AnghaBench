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
 int /*<<< orphan*/  adjust_year_month (int*,int*) ; 
 scalar_t__ isleap (int) ; 

__attribute__((used)) static int
days_per_month(int year, int month)
{
    static const int nominal[] =
    {
	31, 28, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31
    };
    int result;

    adjust_year_month(&year, &month);
    result = nominal[month];
    if (month == 1)
	result += isleap(year);
    return result;
}