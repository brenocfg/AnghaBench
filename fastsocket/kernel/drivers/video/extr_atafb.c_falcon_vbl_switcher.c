#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct falcon_hw {int sync; int /*<<< orphan*/  vid_mode; int /*<<< orphan*/  vid_control; int /*<<< orphan*/  line_offset; int /*<<< orphan*/  line_width; int /*<<< orphan*/  xoffset; scalar_t__ f_shift; scalar_t__ st_shift; scalar_t__ ste_mode; int /*<<< orphan*/  vss; int /*<<< orphan*/  vde; int /*<<< orphan*/  vdb; int /*<<< orphan*/  vbe; int /*<<< orphan*/  vbb; int /*<<< orphan*/  vft; int /*<<< orphan*/  hss; int /*<<< orphan*/  hde; int /*<<< orphan*/  hdb; int /*<<< orphan*/  hbe; int /*<<< orphan*/  hbb; int /*<<< orphan*/  hht; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  line_offset; int /*<<< orphan*/  xoffset; } ;
struct TYPE_8__ {TYPE_1__ falcon; } ;
struct TYPE_12__ {TYPE_2__ hw; } ;
struct TYPE_11__ {int syncmode; } ;
struct TYPE_10__ {int /*<<< orphan*/  off_next; int /*<<< orphan*/  scn_width; } ;
struct TYPE_9__ {int /*<<< orphan*/  xoffset; int /*<<< orphan*/  mode; int /*<<< orphan*/  control; scalar_t__ f_shift; scalar_t__ st_shift; int /*<<< orphan*/  vss; int /*<<< orphan*/  vde; int /*<<< orphan*/  vdb; int /*<<< orphan*/  vbe; int /*<<< orphan*/  vbb; int /*<<< orphan*/  vft; int /*<<< orphan*/  hss; int /*<<< orphan*/  hde; int /*<<< orphan*/  hdb; int /*<<< orphan*/  hbe; int /*<<< orphan*/  hbb; int /*<<< orphan*/  hht; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_6__ current_par ; 
 scalar_t__ f_change_mode ; 
 struct falcon_hw f_new_mode ; 
 scalar_t__ f_pan_display ; 
 TYPE_5__ shifter ; 
 TYPE_4__ shifter_f030 ; 
 TYPE_3__ videl ; 

__attribute__((used)) static irqreturn_t falcon_vbl_switcher(int irq, void *dummy)
{
	struct falcon_hw *hw = &f_new_mode;

	if (f_change_mode) {
		f_change_mode = 0;

		if (hw->sync & 0x1) {
			/* Enable external pixelclock. This code only for ScreenWonder */
			*(volatile unsigned short *)0xffff9202 = 0xffbf;
		} else {
			/* Turn off external clocks. Read sets all output bits to 1. */
			*(volatile unsigned short *)0xffff9202;
		}
		shifter.syncmode = hw->sync;

		videl.hht = hw->hht;
		videl.hbb = hw->hbb;
		videl.hbe = hw->hbe;
		videl.hdb = hw->hdb;
		videl.hde = hw->hde;
		videl.hss = hw->hss;
		videl.vft = hw->vft;
		videl.vbb = hw->vbb;
		videl.vbe = hw->vbe;
		videl.vdb = hw->vdb;
		videl.vde = hw->vde;
		videl.vss = hw->vss;

		videl.f_shift = 0;	/* write enables Falcon palette, 0: 4 planes */
		if (hw->ste_mode) {
			videl.st_shift = hw->st_shift;	/* write enables STE palette */
		} else {
			/* IMPORTANT:
			 * set st_shift 0, so we can tell the screen-depth if f_shift == 0.
			 * Writing 0 to f_shift enables 4 plane Falcon mode but
			 * doesn't set st_shift. st_shift != 0 (!= 4planes) is impossible
			 * with Falcon palette.
			 */
			videl.st_shift = 0;
			/* now back to Falcon palette mode */
			videl.f_shift = hw->f_shift;
		}
		/* writing to st_shift changed scn_width and vid_mode */
		videl.xoffset = hw->xoffset;
		shifter_f030.scn_width = hw->line_width;
		shifter_f030.off_next = hw->line_offset;
		videl.control = hw->vid_control;
		videl.mode = hw->vid_mode;
	}
	if (f_pan_display) {
		f_pan_display = 0;
		videl.xoffset = current_par.hw.falcon.xoffset;
		shifter_f030.off_next = current_par.hw.falcon.line_offset;
	}
	return IRQ_HANDLED;
}