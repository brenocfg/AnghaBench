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
struct TYPE_2__ {scalar_t__ line; scalar_t__ line_length; int /*<<< orphan*/ * next_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curr_line ; 
 int /*<<< orphan*/  down () ; 
 scalar_t__ point ; 
 scalar_t__ position ; 
 int /*<<< orphan*/  right (int /*<<< orphan*/ ) ; 
 scalar_t__ scr_pos ; 

void 
adv_line()	/* advance to beginning of next line	*/
{
	if ((point != curr_line->line) || (scr_pos > 0))
	{
		while (position < curr_line->line_length)
			right(TRUE);
		right(TRUE);
	}
	else if (curr_line->next_line != NULL)
	{
		scr_pos = 0;
		down();
	}
}