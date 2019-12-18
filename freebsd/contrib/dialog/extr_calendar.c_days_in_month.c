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
struct tm {int tm_year; int tm_mon; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_year_month (int*,int*) ; 
 int days_per_month (int,int) ; 

__attribute__((used)) static int
days_in_month(struct tm *current, int offset /* -1, 0, 1 */ )
{
    int year = current->tm_year + 1900;
    int month = current->tm_mon + offset;

    adjust_year_month(&year, &month);
    return days_per_month(year, month);
}