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
struct TYPE_2__ {scalar_t__ line_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curr_line ; 
 int* point ; 
 scalar_t__ position ; 
 int /*<<< orphan*/  right (int /*<<< orphan*/ ) ; 

void 
adv_word()			/* advance to next word		*/
{
while ((position < curr_line->line_length) && ((*point != 32) && (*point != 9)))
		right(TRUE);
while ((position < curr_line->line_length) && ((*point == 32) || (*point == 9)))
		right(TRUE);
}