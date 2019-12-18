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
struct TYPE_2__ {unsigned char CrtMiscIO; int /*<<< orphan*/  ClockingMode; int /*<<< orphan*/  ModeControl; int /*<<< orphan*/  EndVertRetrace; int /*<<< orphan*/  StartVertRetrace; int /*<<< orphan*/  Overflow; int /*<<< orphan*/  EndHorizRetrace; int /*<<< orphan*/  StartHorizRetrace; int /*<<< orphan*/  HorizDisplayEnd; int /*<<< orphan*/  HorizontalTotal; } ;
struct vga16fb_par {TYPE_1__ vga_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_CRT_IC ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 unsigned char vga_io_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_io_w (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  vga_io_wcrt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_io_wseq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga_vesa_unblank(struct vga16fb_par *par)
{
	unsigned char SeqCtrlIndex = vga_io_r(VGA_SEQ_I);
	unsigned char CrtCtrlIndex = vga_io_r(VGA_CRT_IC);
	
	/* restore original values of VGA controller registers */
	vga_io_w(VGA_MIS_W, par->vga_state.CrtMiscIO);

	/* HorizontalTotal */
	vga_io_wcrt(0x00, par->vga_state.HorizontalTotal);
	/* HorizDisplayEnd */
	vga_io_wcrt(0x01, par->vga_state.HorizDisplayEnd);
	/* StartHorizRetrace */
	vga_io_wcrt(0x04, par->vga_state.StartHorizRetrace);
	/* EndHorizRetrace */
	vga_io_wcrt(0x05, par->vga_state.EndHorizRetrace);
	/* Overflow */
	vga_io_wcrt(0x07, par->vga_state.Overflow);
	/* StartVertRetrace */
	vga_io_wcrt(0x10, par->vga_state.StartVertRetrace);
	/* EndVertRetrace */
	vga_io_wcrt(0x11, par->vga_state.EndVertRetrace);
	/* ModeControl */
	vga_io_wcrt(0x17, par->vga_state.ModeControl);
	/* ClockingMode */
	vga_io_wseq(0x01, par->vga_state.ClockingMode);

	/* restore index/control registers */
	vga_io_w(VGA_SEQ_I, SeqCtrlIndex);
	vga_io_w(VGA_CRT_IC, CrtCtrlIndex);
}