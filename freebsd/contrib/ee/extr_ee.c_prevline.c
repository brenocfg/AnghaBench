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
struct TYPE_2__ {int line_length; int /*<<< orphan*/  line; struct TYPE_2__* prev_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  absolute_lin ; 
 TYPE_1__* curr_line ; 
 int /*<<< orphan*/  draw_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  point ; 
 int position ; 
 scalar_t__ scr_vert ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  winsertln (int /*<<< orphan*/ ) ; 

void 
prevline()			/* move pointers to start of previous line*/
{
	curr_line = curr_line->prev_line;
	absolute_lin--;
	point = curr_line->line;
	position = 1;
	if (scr_vert == 0)
	{
		winsertln(text_win);
		draw_line(0,0,point,1,curr_line->line_length);
	}
	else
		scr_vert--;
	while (position < curr_line->line_length)
	{
		position++;
		point++;
	}
}