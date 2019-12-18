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
struct TYPE_2__ {int /*<<< orphan*/  line; struct TYPE_2__* prev_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  absolute_lin ; 
 TYPE_1__* curr_line ; 
 scalar_t__ horiz_offset ; 
 int /*<<< orphan*/  midscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point ; 
 int position ; 
 int /*<<< orphan*/  scr_horz ; 
 int /*<<< orphan*/  scr_pos ; 

void 
top()				/* go to top of file			*/
{
	while (curr_line->prev_line != NULL)
	{
		curr_line = curr_line->prev_line;
		absolute_lin--;
	}
	point = curr_line->line;
	if (horiz_offset)
		horiz_offset = 0;
	position = 1;
	midscreen(0, point);
	scr_pos = scr_horz;
}