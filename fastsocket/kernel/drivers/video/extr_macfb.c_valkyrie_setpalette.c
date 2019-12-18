#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  nubus_writeb (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* valkyrie_cmap_regs ; 

__attribute__((used)) static int valkyrie_setpalette (unsigned int regno, unsigned int red,
				unsigned int green, unsigned int blue,
				struct fb_info *info)
{
	unsigned long flags;
	
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	local_irq_save(flags);
	
	/* tell clut which address to fill */
	nubus_writeb(regno, &valkyrie_cmap_regs->addr);
	nop();

	/* send one color channel at a time */
	nubus_writeb(red, &valkyrie_cmap_regs->lut);
	nop();
	nubus_writeb(green, &valkyrie_cmap_regs->lut);
	nop();
	nubus_writeb(blue, &valkyrie_cmap_regs->lut);

	local_irq_restore(flags);
	return 0;
}