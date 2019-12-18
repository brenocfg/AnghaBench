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
struct TYPE_2__ {int CrtMiscIO; int Overflow; int ClockingMode; void* ModeControl; void* EndVertRetrace; void* StartVertRetrace; void* EndHorizRetrace; void* StartHorizRetrace; void* HorizDisplayEnd; void* HorizontalTotal; } ;
struct vga16fb_par {TYPE_1__ vga_state; int /*<<< orphan*/  vesa_blanked; } ;

/* Variables and functions */
 int FB_BLANK_HSYNC_SUSPEND ; 
 int FB_BLANK_VSYNC_SUSPEND ; 
 int /*<<< orphan*/  VGA_CRTC_H_SYNC_END ; 
 int /*<<< orphan*/  VGA_CRTC_H_SYNC_START ; 
 int /*<<< orphan*/  VGA_CRTC_OVERFLOW ; 
 int /*<<< orphan*/  VGA_CRTC_V_SYNC_END ; 
 int /*<<< orphan*/  VGA_CRTC_V_SYNC_START ; 
 int /*<<< orphan*/  VGA_CRT_IC ; 
 int /*<<< orphan*/  VGA_MIS_R ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 
 void* vga_io_r (int /*<<< orphan*/ ) ; 
 void* vga_io_rcrt (int) ; 
 int vga_io_rseq (int) ; 
 int /*<<< orphan*/  vga_io_w (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_io_wcrt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_io_wseq (int,int) ; 

__attribute__((used)) static void vga_vesa_blank(struct vga16fb_par *par, int mode)
{
	unsigned char SeqCtrlIndex = vga_io_r(VGA_SEQ_I);
	unsigned char CrtCtrlIndex = vga_io_r(VGA_CRT_IC);
	
	/* save original values of VGA controller registers */
	if(!par->vesa_blanked) {
		par->vga_state.CrtMiscIO = vga_io_r(VGA_MIS_R);
		//sti();

		par->vga_state.HorizontalTotal = vga_io_rcrt(0x00);	/* HorizontalTotal */
		par->vga_state.HorizDisplayEnd = vga_io_rcrt(0x01);	/* HorizDisplayEnd */
		par->vga_state.StartHorizRetrace = vga_io_rcrt(0x04);	/* StartHorizRetrace */
		par->vga_state.EndHorizRetrace = vga_io_rcrt(0x05);	/* EndHorizRetrace */
		par->vga_state.Overflow = vga_io_rcrt(0x07);		/* Overflow */
		par->vga_state.StartVertRetrace = vga_io_rcrt(0x10);	/* StartVertRetrace */
		par->vga_state.EndVertRetrace = vga_io_rcrt(0x11);	/* EndVertRetrace */
		par->vga_state.ModeControl = vga_io_rcrt(0x17);	/* ModeControl */
		par->vga_state.ClockingMode = vga_io_rseq(0x01);	/* ClockingMode */
	}

	/* assure that video is enabled */
	/* "0x20" is VIDEO_ENABLE_bit in register 01 of sequencer */
	vga_io_wseq(0x01, par->vga_state.ClockingMode | 0x20);

	/* test for vertical retrace in process.... */
	if ((par->vga_state.CrtMiscIO & 0x80) == 0x80)
		vga_io_w(VGA_MIS_W, par->vga_state.CrtMiscIO & 0xef);

	/*
	 * Set <End of vertical retrace> to minimum (0) and
	 * <Start of vertical Retrace> to maximum (incl. overflow)
	 * Result: turn off vertical sync (VSync) pulse.
	 */
	if (mode & FB_BLANK_VSYNC_SUSPEND) {
		vga_io_wcrt(VGA_CRTC_V_SYNC_START, 0xff);
		vga_io_wcrt(VGA_CRTC_V_SYNC_END, 0x40);
		/* bits 9,10 of vert. retrace */
		vga_io_wcrt(VGA_CRTC_OVERFLOW, par->vga_state.Overflow | 0x84);
	}

	if (mode & FB_BLANK_HSYNC_SUSPEND) {
		/*
		 * Set <End of horizontal retrace> to minimum (0) and
		 *  <Start of horizontal Retrace> to maximum
		 * Result: turn off horizontal sync (HSync) pulse.
		 */
		vga_io_wcrt(VGA_CRTC_H_SYNC_START, 0xff);
		vga_io_wcrt(VGA_CRTC_H_SYNC_END, 0x00);
	}

	/* restore both index registers */
	outb_p(SeqCtrlIndex, VGA_SEQ_I);
	outb_p(CrtCtrlIndex, VGA_CRT_IC);
}