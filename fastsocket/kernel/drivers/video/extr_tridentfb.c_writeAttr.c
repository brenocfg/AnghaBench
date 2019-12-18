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
struct tridentfb_par {scalar_t__ io_virt; } ;

/* Variables and functions */
 scalar_t__ VGA_IS1_RC ; 
 int /*<<< orphan*/  fb_readb (scalar_t__) ; 
 int /*<<< orphan*/  vga_mm_wattr (scalar_t__,int,unsigned char) ; 

__attribute__((used)) static inline void writeAttr(struct tridentfb_par *par, int reg,
			     unsigned char val)
{
	fb_readb(par->io_virt + VGA_IS1_RC);	/* flip-flop to index */
	vga_mm_wattr(par->io_virt, reg, val);
}