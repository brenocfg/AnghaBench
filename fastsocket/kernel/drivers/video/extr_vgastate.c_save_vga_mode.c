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
struct vgastate {int num_crtc; int num_attr; int num_gfx; int num_seq; int /*<<< orphan*/  vgabase; scalar_t__ vidstate; } ;
struct regstate {int misc; int /*<<< orphan*/ * seq; int /*<<< orphan*/ * gfx; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_ATT_W ; 
 unsigned short VGA_MIS_R ; 
 int vga_r (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  vga_rattr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_rcrtcs (int /*<<< orphan*/ ,unsigned short,int) ; 
 int /*<<< orphan*/  vga_rgfx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_rseq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void save_vga_mode(struct vgastate *state)
{
	struct regstate *saved = (struct regstate *) state->vidstate;
	unsigned short iobase;
	int i;

	saved->misc = vga_r(state->vgabase, VGA_MIS_R);
	if (saved->misc & 1)
		iobase = 0x3d0;
	else
		iobase = 0x3b0;

	for (i = 0; i < state->num_crtc; i++) 
		saved->crtc[i] = vga_rcrtcs(state->vgabase, iobase, i);
	
	vga_r(state->vgabase, iobase + 0xa); 
	vga_w(state->vgabase, VGA_ATT_W, 0x00);
	for (i = 0; i < state->num_attr; i++) {
		vga_r(state->vgabase, iobase + 0xa);
		saved->attr[i] = vga_rattr(state->vgabase, i);
	}
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);

	for (i = 0; i < state->num_gfx; i++) 
		saved->gfx[i] = vga_rgfx(state->vgabase, i);

	for (i = 0; i < state->num_seq; i++) 
		saved->seq[i] = vga_rseq(state->vgabase, i);
}