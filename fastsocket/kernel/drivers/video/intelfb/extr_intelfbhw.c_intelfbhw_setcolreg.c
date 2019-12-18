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
typedef  scalar_t__ u32 ;
struct intelfb_info {scalar_t__ pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  OUTREG (scalar_t__,unsigned int) ; 
 unsigned int PALETTE_8_BLUE_SHIFT ; 
 unsigned int PALETTE_8_GREEN_SHIFT ; 
 unsigned int PALETTE_8_RED_SHIFT ; 
 scalar_t__ PALETTE_A ; 
 scalar_t__ PALETTE_B ; 
 scalar_t__ PIPE_A ; 

void intelfbhw_setcolreg(struct intelfb_info *dinfo, unsigned regno,
			 unsigned red, unsigned green, unsigned blue,
			 unsigned transp)
{
	u32 palette_reg = (dinfo->pipe == PIPE_A) ?
			  PALETTE_A : PALETTE_B;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_setcolreg: %d: (%d, %d, %d)\n",
		regno, red, green, blue);
#endif

	OUTREG(palette_reg + (regno << 2),
	       (red << PALETTE_8_RED_SHIFT) |
	       (green << PALETTE_8_GREEN_SHIFT) |
	       (blue << PALETTE_8_BLUE_SHIFT));
}