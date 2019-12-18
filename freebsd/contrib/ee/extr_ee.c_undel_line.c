#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int line_length; } ;
struct TYPE_4__ {int /*<<< orphan*/  line_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curr_line ; 
 unsigned char* d_line ; 
 TYPE_2__* dlt_line ; 
 int /*<<< orphan*/  draw_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  left (int /*<<< orphan*/ ) ; 
 unsigned char* point ; 
 int /*<<< orphan*/  position ; 
 unsigned char* resiz_line (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_horz ; 
 int /*<<< orphan*/  scr_vert ; 

void 
undel_line()			/* undelete last deleted line		*/
{
	unsigned char *ud1;
	unsigned char *ud2;
	int tposit;

	if (dlt_line->line_length == 0)
		return;

	insert_line(TRUE);
	left(TRUE);
	point = resiz_line(dlt_line->line_length, curr_line, position);
	curr_line->line_length += dlt_line->line_length - 1;
	ud1 = point;
	ud2 = d_line;
	tposit = 1;
	while (tposit < dlt_line->line_length)
	{
		tposit++;
		*ud1 = *ud2;
		ud1++;
		ud2++;
	}
	*ud1 = '\0';
	draw_line(scr_vert, scr_horz,point,position,curr_line->line_length);
}