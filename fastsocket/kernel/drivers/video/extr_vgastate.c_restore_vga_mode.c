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
struct vgastate {int num_seq; int num_crtc; int num_gfx; int num_attr; int /*<<< orphan*/  vgabase; scalar_t__ vidstate; } ;
struct regstate {int misc; int* seq; int* crtc; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_ATT_W ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 size_t VGA_SEQ_CLOCK_MODE ; 
 size_t VGA_SEQ_RESET ; 
 int /*<<< orphan*/  vga_r (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wcrtcs (int /*<<< orphan*/ ,unsigned short,int,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void restore_vga_mode(struct vgastate *state)
{
	struct regstate *saved = (struct regstate *) state->vidstate;
	unsigned short iobase;
	int i;

	vga_w(state->vgabase, VGA_MIS_W, saved->misc);

	if (saved->misc & 1)
		iobase = 0x3d0;
	else
		iobase = 0x3b0;

	/* turn off display */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, 
		 saved->seq[VGA_SEQ_CLOCK_MODE] | 0x20);

	/* disable sequencer */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x01);
	
	/* enable palette addressing */
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x00);

	for (i = 2; i < state->num_seq; i++) 
		vga_wseq(state->vgabase, i, saved->seq[i]);


	/* unprotect vga regs */
	vga_wcrtcs(state->vgabase, iobase, 17, saved->crtc[17] & ~0x80);
	for (i = 0; i < state->num_crtc; i++) 
		vga_wcrtcs(state->vgabase, iobase, i, saved->crtc[i]);
	
	for (i = 0; i < state->num_gfx; i++) 
		vga_wgfx(state->vgabase, i, saved->gfx[i]);

	for (i = 0; i < state->num_attr; i++) {
		vga_r(state->vgabase, iobase + 0xa);
		vga_wattr(state->vgabase, i, saved->attr[i]);
	}

	/* reenable sequencer */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);
	/* turn display on */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, 
		 saved->seq[VGA_SEQ_CLOCK_MODE] & ~(1 << 5));

	/* disable video/palette source */
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);
}