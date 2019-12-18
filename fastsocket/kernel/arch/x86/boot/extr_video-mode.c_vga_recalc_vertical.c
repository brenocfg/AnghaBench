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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int force_y ; 
 int in_idx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_idx (int,int /*<<< orphan*/ ,int) ; 
 int rdfs8 (int) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_crtc () ; 

__attribute__((used)) static void vga_recalc_vertical(void)
{
	unsigned int font_size, rows;
	u16 crtc;
	u8 pt, ov;

	set_fs(0);
	font_size = rdfs8(0x485); /* BIOS: font size (pixels) */
	rows = force_y ? force_y : rdfs8(0x484)+1; /* Text rows */

	rows *= font_size;	/* Visible scan lines */
	rows--;			/* ... minus one */

	crtc = vga_crtc();

	pt = in_idx(crtc, 0x11);
	pt &= ~0x80;		/* Unlock CR0-7 */
	out_idx(pt, crtc, 0x11);

	out_idx((u8)rows, crtc, 0x12); /* Lower height register */

	ov = in_idx(crtc, 0x07); /* Overflow register */
	ov &= 0xbd;
	ov |= (rows >> (8-1)) & 0x02;
	ov |= (rows >> (9-6)) & 0x40;
	out_idx(ov, crtc, 0x07);
}