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
struct tm {int tm_mday; int tm_wday; } ;

/* Variables and functions */
 int MAX_DAYS ; 

__attribute__((used)) static int
day_cell_number(struct tm *current)
{
    int cell;
    cell = current->tm_mday - ((6 + current->tm_mday - current->tm_wday) % MAX_DAYS);
    if ((current->tm_mday - 1) % MAX_DAYS != current->tm_wday)
	cell += 6;
    else
	cell--;
    return cell;
}