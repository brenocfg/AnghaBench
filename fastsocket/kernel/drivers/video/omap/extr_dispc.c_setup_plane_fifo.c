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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int const DISPC_GFX_FIFO_SIZE_STATUS ; 
 int const DISPC_GFX_FIFO_THRESHOLD ; 
 int const DISPC_VID1_BASE ; 
 int const DISPC_VID2_BASE ; 
 int const DISPC_VID_FIFO_SIZE_STATUS ; 
 int const DISPC_VID_FIFO_THRESHOLD ; 
 int FLD_MASK (int,int) ; 
 int /*<<< orphan*/  MOD_REG_FLD (int const,int,int) ; 
 int dispc_read_reg (int const) ; 

__attribute__((used)) static void setup_plane_fifo(int plane, int ext_mode)
{
	const u32 ftrs_reg[] = { DISPC_GFX_FIFO_THRESHOLD,
				DISPC_VID1_BASE + DISPC_VID_FIFO_THRESHOLD,
			        DISPC_VID2_BASE + DISPC_VID_FIFO_THRESHOLD };
	const u32 fsz_reg[] = { DISPC_GFX_FIFO_SIZE_STATUS,
				DISPC_VID1_BASE + DISPC_VID_FIFO_SIZE_STATUS,
				DISPC_VID2_BASE + DISPC_VID_FIFO_SIZE_STATUS };
	int low, high;
	u32 l;

	BUG_ON(plane > 2);

	l = dispc_read_reg(fsz_reg[plane]);
	l &= FLD_MASK(0, 11);
	if (ext_mode) {
		low = l * 3 / 4;
		high = l;
	} else {
		low = l / 4;
		high = l * 3 / 4;
	}
	MOD_REG_FLD(ftrs_reg[plane], FLD_MASK(16, 12) | FLD_MASK(0, 12),
			(high << 16) | low);
}