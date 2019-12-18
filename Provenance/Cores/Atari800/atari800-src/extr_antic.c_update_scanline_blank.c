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

/* Variables and functions */
 int ANTIC_HSCROL ; 
 int* ANTIC_cpu2antic_ptr ; 
 int ANTIC_cur_screen_pos ; 
 size_t ANTIC_xpos ; 
 int IR ; 
 int /*<<< orphan*/  draw_partial_scanline (int,int) ; 

void update_scanline_blank(void)
{
	int actual_xpos = ANTIC_cpu2antic_ptr[ANTIC_xpos];
	int hscrol_adj = (IR & 0x10) ? ANTIC_HSCROL : 0;
	int hscrollsb_adj = (hscrol_adj & 1);
	int newpos;

	/* empirically determined: adjustment of 7 */
	newpos = actual_xpos * 2 - 37 + hscrollsb_adj + 7;
	draw_partial_scanline(ANTIC_cur_screen_pos, newpos);
	ANTIC_cur_screen_pos = newpos;
}