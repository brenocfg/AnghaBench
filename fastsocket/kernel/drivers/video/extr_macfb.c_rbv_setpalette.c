#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; } ;
struct TYPE_4__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; int /*<<< orphan*/  cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  nubus_writeb (unsigned char,int /*<<< orphan*/ *) ; 
 TYPE_2__* rbv_cmap_regs ; 

__attribute__((used)) static int rbv_setpalette (unsigned int regno, unsigned int red,
			   unsigned int green, unsigned int blue,
			   struct fb_info *info)
{
	/* use MSBs */
	unsigned char _red  =red>>8;
	unsigned char _green=green>>8;
	unsigned char _blue =blue>>8;
	unsigned char _regno;
	unsigned long flags;

	if (info->var.bits_per_pixel > 8) return 1; /* failsafe */

	local_irq_save(flags);
	
	/* From the VideoToolbox driver.  Seems to be saying that
	 * regno #254 and #255 are the important ones for 1-bit color,
	 * regno #252-255 are the important ones for 2-bit color, etc.
	 */
	_regno = regno + (256-(1 << info->var.bits_per_pixel));

	/* reset clut? (VideoToolbox sez "not necessary") */
	nubus_writeb(0xFF, &rbv_cmap_regs->cntl); nop();
	
	/* tell clut which address to use. */
	nubus_writeb(_regno, &rbv_cmap_regs->addr); nop();
	
	/* send one color channel at a time. */
	nubus_writeb(_red,   &rbv_cmap_regs->lut); nop();
	nubus_writeb(_green, &rbv_cmap_regs->lut); nop();
	nubus_writeb(_blue,  &rbv_cmap_regs->lut);
	
	local_irq_restore(flags); /* done. */
	return 0;
}