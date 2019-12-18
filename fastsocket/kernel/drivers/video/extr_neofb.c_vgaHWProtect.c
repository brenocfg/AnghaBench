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

/* Variables and functions */
 int /*<<< orphan*/  VGAdisablePalette () ; 
 int /*<<< orphan*/  VGAenablePalette () ; 
 unsigned char vga_rseq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void vgaHWProtect(int on)
{
	unsigned char tmp;

	tmp = vga_rseq(NULL, 0x01);
	if (on) {
		/*
		 * Turn off screen and disable sequencer.
		 */
		vga_wseq(NULL, 0x00, 0x01);		/* Synchronous Reset */
		vga_wseq(NULL, 0x01, tmp | 0x20);	/* disable the display */

		VGAenablePalette();
	} else {
		/*
		 * Reenable sequencer, then turn on screen.
		 */
		vga_wseq(NULL, 0x01, tmp & ~0x20);	/* reenable display */
		vga_wseq(NULL, 0x00, 0x03);		/* clear synchronousreset */

		VGAdisablePalette();
	}
}