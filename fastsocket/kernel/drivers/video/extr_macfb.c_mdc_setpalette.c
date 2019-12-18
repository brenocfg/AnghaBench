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
struct mdc_cmap_regs {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 struct mdc_cmap_regs* nubus_slot_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nubus_writeb (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_slot ; 

__attribute__((used)) static int mdc_setpalette(unsigned int regno, unsigned int red,
			  unsigned int green, unsigned int blue,
			  struct fb_info *info)
{
	volatile struct mdc_cmap_regs *cmap_regs =
		nubus_slot_addr(video_slot);
	/* use MSBs */
	unsigned char _red  =red>>8;
	unsigned char _green=green>>8;
	unsigned char _blue =blue>>8;
	unsigned char _regno=regno;
	unsigned long flags;

	local_irq_save(flags);
	
	/* the nop's are there to order writes. */
	nubus_writeb(_regno, &cmap_regs->addr); nop();
	nubus_writeb(_red, &cmap_regs->lut);    nop();
	nubus_writeb(_green, &cmap_regs->lut);  nop();
	nubus_writeb(_blue, &cmap_regs->lut);

	local_irq_restore(flags);
	return 0;
}