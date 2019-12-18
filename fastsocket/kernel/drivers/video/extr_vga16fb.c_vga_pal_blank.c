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
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga_pal_blank(void)
{
	int i;

	for (i=0; i<16; i++) {
		outb_p(i, VGA_PEL_IW);
		outb_p(0, VGA_PEL_D);
		outb_p(0, VGA_PEL_D);
		outb_p(0, VGA_PEL_D);
	}
}