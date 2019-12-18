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
 int inb (int) ; 
 int /*<<< orphan*/  out_idx (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  vga_crtc () ; 

__attribute__((used)) static void vga_set_480_scanlines(void)
{
	u16 crtc;		/* CRTC base address */
	u8  csel;		/* CRTC miscellaneous output register */

	crtc = vga_crtc();

	out_idx(0x0c, crtc, 0x11); /* Vertical sync end, unlock CR0-7 */
	out_idx(0x0b, crtc, 0x06); /* Vertical total */
	out_idx(0x3e, crtc, 0x07); /* Vertical overflow */
	out_idx(0xea, crtc, 0x10); /* Vertical sync start */
	out_idx(0xdf, crtc, 0x12); /* Vertical display end */
	out_idx(0xe7, crtc, 0x15); /* Vertical blank start */
	out_idx(0x04, crtc, 0x16); /* Vertical blank end */
	csel = inb(0x3cc);
	csel &= 0x0d;
	csel |= 0xe2;
	outb(csel, 0x3c2);
}