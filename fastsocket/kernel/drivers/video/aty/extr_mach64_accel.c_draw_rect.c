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
typedef  int u16 ;
struct atyfb_par {int blitter_may_be_busy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DST_HEIGHT_WIDTH ; 
 int /*<<< orphan*/  DST_Y_X ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  wait_for_fifo (int,struct atyfb_par*) ; 

__attribute__((used)) static inline void draw_rect(s16 x, s16 y, u16 width, u16 height,
			     struct atyfb_par *par)
{
	/* perform rectangle fill */
	wait_for_fifo(2, par);
	aty_st_le32(DST_Y_X, (x << 16) | y, par);
	aty_st_le32(DST_HEIGHT_WIDTH, (width << 16) | height, par);
	par->blitter_may_be_busy = 1;
}