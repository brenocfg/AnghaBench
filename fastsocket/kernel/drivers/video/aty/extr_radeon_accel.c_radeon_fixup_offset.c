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
struct radeonfb_info {int fb_local_base; int pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PITCH_OFFSET ; 
 int /*<<< orphan*/  DST_PITCH_OFFSET ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_FB_LOCATION ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRC_PITCH_OFFSET ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 

__attribute__((used)) static void radeon_fixup_offset(struct radeonfb_info *rinfo)
{
	u32 local_base;

	/* *** Ugly workaround *** */
	/*
	 * On some platforms, the video memory is mapped at 0 in radeon chip space
	 * (like PPCs) by the firmware. X will always move it up so that it's seen
	 * by the chip to be at the same address as the PCI BAR.
	 * That means that when switching back from X, there is a mismatch between
	 * the offsets programmed into the engine. This means that potentially,
	 * accel operations done before radeonfb has a chance to re-init the engine
	 * will have incorrect offsets, and potentially trash system memory !
	 *
	 * The correct fix is for fbcon to never call any accel op before the engine
	 * has properly been re-initialized (by a call to set_var), but this is a
	 * complex fix. This workaround in the meantime, called before every accel
	 * operation, makes sure the offsets are in sync.
	 */

	radeon_fifo_wait (1);
	local_base = INREG(MC_FB_LOCATION) << 16;
	if (local_base == rinfo->fb_local_base)
		return;

	rinfo->fb_local_base = local_base;

	radeon_fifo_wait (3);
	OUTREG(DEFAULT_PITCH_OFFSET, (rinfo->pitch << 0x16) |
				     (rinfo->fb_local_base >> 10));
	OUTREG(DST_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
	OUTREG(SRC_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
}