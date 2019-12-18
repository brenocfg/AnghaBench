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
struct TYPE_2__ {int /*<<< orphan*/  v_columns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_NONE ; 
 int /*<<< orphan*/  gc_paint_char (unsigned int,unsigned int,char,int /*<<< orphan*/ ) ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void 
gc_clear_line(unsigned int xx, unsigned int yy, int which)
{
	unsigned int start, end, i;

	/*
	 * This routine runs extremely slowly.  I don't think it's
	 * used all that often, except for To end of line.  I'll go
	 * back and speed this up when I speed up the whole vc
	 * module. --LK
	 */

	switch (which) {
	case 0:		/* To end of line	 */
		start = xx;
		end = vinfo.v_columns-1;
		break;
	case 1:		/* To start of line	 */
		start = 0;
		end = xx;
		break;
	case 2:		/* Whole line		 */
		start = 0;
		end = vinfo.v_columns-1;
		break;
	default:
		return;
	}

	for (i = start; i <= end; i++) {
		gc_paint_char(i, yy, ' ', ATTR_NONE);
	}
}