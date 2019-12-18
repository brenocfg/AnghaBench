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
struct vgastate {int /*<<< orphan*/  vgabase; } ;
struct TYPE_2__ {int SeqCtrlIndex; int CrtCtrlIndex; int CrtMiscIO; int Overflow; int ClockingMode; void* ModeControl; void* EndVertRetrace; void* StartVertRetrace; void* EndHorizRetrace; void* StartHorizRetrace; void* HorizDisplayEnd; void* HorizontalTotal; } ;

/* Variables and functions */
 int VESA_HSYNC_SUSPEND ; 
 int VESA_VSYNC_SUSPEND ; 
 int /*<<< orphan*/  VGA_MIS_R ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 void* inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_lock ; 
 void* vga_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_rseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vga_state ; 
 int /*<<< orphan*/  vga_vesa_blanked ; 
 int /*<<< orphan*/  vga_video_port_reg ; 
 int /*<<< orphan*/  vga_video_port_val ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vga_vesa_blank(struct vgastate *state, int mode)
{
	/* save original values of VGA controller registers */
	if (!vga_vesa_blanked) {
		spin_lock_irq(&vga_lock);
		vga_state.SeqCtrlIndex = vga_r(state->vgabase, VGA_SEQ_I);
		vga_state.CrtCtrlIndex = inb_p(vga_video_port_reg);
		vga_state.CrtMiscIO = vga_r(state->vgabase, VGA_MIS_R);
		spin_unlock_irq(&vga_lock);

		outb_p(0x00, vga_video_port_reg);	/* HorizontalTotal */
		vga_state.HorizontalTotal = inb_p(vga_video_port_val);
		outb_p(0x01, vga_video_port_reg);	/* HorizDisplayEnd */
		vga_state.HorizDisplayEnd = inb_p(vga_video_port_val);
		outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
		vga_state.StartHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
		vga_state.EndHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x07, vga_video_port_reg);	/* Overflow */
		vga_state.Overflow = inb_p(vga_video_port_val);
		outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
		vga_state.StartVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
		vga_state.EndVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x17, vga_video_port_reg);	/* ModeControl */
		vga_state.ModeControl = inb_p(vga_video_port_val);
		vga_state.ClockingMode = vga_rseq(state->vgabase, VGA_SEQ_CLOCK_MODE);
	}

	/* assure that video is enabled */
	/* "0x20" is VIDEO_ENABLE_bit in register 01 of sequencer */
	spin_lock_irq(&vga_lock);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, vga_state.ClockingMode | 0x20);

	/* test for vertical retrace in process.... */
	if ((vga_state.CrtMiscIO & 0x80) == 0x80)
		vga_w(state->vgabase, VGA_MIS_W, vga_state.CrtMiscIO & 0xEF);

	/*
	 * Set <End of vertical retrace> to minimum (0) and
	 * <Start of vertical Retrace> to maximum (incl. overflow)
	 * Result: turn off vertical sync (VSync) pulse.
	 */
	if (mode & VESA_VSYNC_SUSPEND) {
		outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
		outb_p(0xff, vga_video_port_val);	/* maximum value */
		outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
		outb_p(0x40, vga_video_port_val);	/* minimum (bits 0..3)  */
		outb_p(0x07, vga_video_port_reg);	/* Overflow */
		outb_p(vga_state.Overflow | 0x84, vga_video_port_val);	/* bits 9,10 of vert. retrace */
	}

	if (mode & VESA_HSYNC_SUSPEND) {
		/*
		 * Set <End of horizontal retrace> to minimum (0) and
		 *  <Start of horizontal Retrace> to maximum
		 * Result: turn off horizontal sync (HSync) pulse.
		 */
		outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
		outb_p(0xff, vga_video_port_val);	/* maximum */
		outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
		outb_p(0x00, vga_video_port_val);	/* minimum (0) */
	}

	/* restore both index registers */
	vga_w(state->vgabase, VGA_SEQ_I, vga_state.SeqCtrlIndex);
	outb_p(vga_state.CrtCtrlIndex, vga_video_port_reg);
	spin_unlock_irq(&vga_lock);
}