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
struct TYPE_2__ {int /*<<< orphan*/  line_length; int /*<<< orphan*/  line; struct TYPE_2__* next_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  absolute_lin ; 
 TYPE_1__* curr_line ; 
 int /*<<< orphan*/  draw_line (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ last_line ; 
 int /*<<< orphan*/  point ; 
 int position ; 
 scalar_t__ scr_vert ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdeleteln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void 
nextline()			/* move pointers to start of next line	*/
{
	curr_line = curr_line->next_line;
	absolute_lin++;
	point = curr_line->line;
	position = 1;
	if (scr_vert == last_line)
	{
		wmove(text_win, 0,0);
		wdeleteln(text_win);
		wmove(text_win, last_line,0);
		wclrtobot(text_win);
		draw_line(last_line,0,point,1,curr_line->line_length);
	}
	else
		scr_vert++;
}