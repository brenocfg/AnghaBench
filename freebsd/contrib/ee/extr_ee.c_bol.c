#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ line; int /*<<< orphan*/ * prev_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curr_line ; 
 int /*<<< orphan*/  left (int /*<<< orphan*/ ) ; 
 scalar_t__ point ; 
 scalar_t__ scr_pos ; 
 int /*<<< orphan*/  up () ; 

void 
bol()				/* move to beginning of line	*/
{
	if (point != curr_line->line)
	{
		while (point != curr_line->line)
			left(TRUE);
	}
	else if (curr_line->prev_line != NULL)
	{
		scr_pos = 0;
		up();
	}
}