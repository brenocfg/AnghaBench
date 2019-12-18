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
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGAdisablePalette (struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAenablePalette (struct savagefb_par*) ; 
 unsigned char VGArSEQ (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwSEQ (int,unsigned char,struct savagefb_par*) ; 
 int /*<<< orphan*/  vgaHWSeqReset (struct savagefb_par*,int) ; 

__attribute__((used)) static void vgaHWProtect(struct savagefb_par *par, int on)
{
	unsigned char tmp;

	if (on) {
		/*
		 * Turn off screen and disable sequencer.
		 */
		tmp = VGArSEQ(0x01, par);

		vgaHWSeqReset(par, 1);	        /* start synchronous reset */
		VGAwSEQ(0x01, tmp | 0x20, par);/* disable the display */

		VGAenablePalette(par);
	} else {
		/*
		 * Reenable sequencer, then turn on screen.
		 */

		tmp = VGArSEQ(0x01, par);

		VGAwSEQ(0x01, tmp & ~0x20, par);/* reenable display */
		vgaHWSeqReset(par, 0);	        /* clear synchronous reset */

		VGAdisablePalette(par);
	}
}