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
 int MAX_MONTHS ; 

__attribute__((used)) static void
adjust_year_month(int *year, int *month)
{
    while (*month < 0) {
	*month += MAX_MONTHS;
	*year -= 1;
    }
    while (*month >= MAX_MONTHS) {
	*month -= MAX_MONTHS;
	*year += 1;
    }
}