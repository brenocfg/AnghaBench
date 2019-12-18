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
struct TYPE_4__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  status2; scalar_t__ vbl_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ CIVIC_VBL_OFFSET ; 
 TYPE_2__* civic_cmap_regs ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 void* nubus_readb (int /*<<< orphan*/ *) ; 
 unsigned long* nubus_readl (scalar_t__) ; 
 int /*<<< orphan*/  nubus_writeb (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int civic_setpalette (unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     struct fb_info *info)
{
	static int lastreg = -1;
	unsigned long flags;
	int clut_status;
	
	if (info->var.bits_per_pixel > 8) return 1; /* failsafe */

	red   >>= 8;
	green >>= 8;
	blue  >>= 8;

	local_irq_save(flags);
	
	/*
	 * Set the register address
	 */
	nubus_writeb(regno, &civic_cmap_regs->addr); nop();

	/*
	 * Wait for VBL interrupt here;
	 * They're usually not enabled from Penguin, so we won't check
	 */
#if 0
	{
#define CIVIC_VBL_OFFSET	0x120
		volatile unsigned long *vbl = nubus_readl(civic_cmap_regs->vbl_addr + CIVIC_VBL_OFFSET);
		/* do interrupt setup stuff here? */
		*vbl = 0L; nop();	/* clear */
		*vbl = 1L; nop();	/* set */
		while (*vbl != 0L)	/* wait for next vbl */
		{
			usleep(10);	/* needed? */
		}
		/* do interrupt shutdown stuff here? */
	}
#endif

	/*
	 * Grab a status word and do some checking;
	 * Then finally write the clut!
	 */
	clut_status =  nubus_readb(&civic_cmap_regs->status2);

	if ((clut_status & 0x0008) == 0)
	{
#if 0
		if ((clut_status & 0x000D) != 0)
		{
			nubus_writeb(0x00, &civic_cmap_regs->lut); nop();
			nubus_writeb(0x00, &civic_cmap_regs->lut); nop();
		}
#endif

		nubus_writeb(  red, &civic_cmap_regs->lut); nop();
		nubus_writeb(green, &civic_cmap_regs->lut); nop();
		nubus_writeb( blue, &civic_cmap_regs->lut); nop();
		nubus_writeb( 0x00, &civic_cmap_regs->lut); nop();
	}
	else
	{
		unsigned char junk;

		junk = nubus_readb(&civic_cmap_regs->lut); nop();
		junk = nubus_readb(&civic_cmap_regs->lut); nop();
		junk = nubus_readb(&civic_cmap_regs->lut); nop();
		junk = nubus_readb(&civic_cmap_regs->lut); nop();

		if ((clut_status & 0x000D) != 0)
		{
			nubus_writeb(0x00, &civic_cmap_regs->lut); nop();
			nubus_writeb(0x00, &civic_cmap_regs->lut); nop();
		}

		nubus_writeb(  red, &civic_cmap_regs->lut); nop();
		nubus_writeb(green, &civic_cmap_regs->lut); nop();
		nubus_writeb( blue, &civic_cmap_regs->lut); nop();
		nubus_writeb( junk, &civic_cmap_regs->lut); nop();
	}

	local_irq_restore(flags);
	lastreg = regno;
	return 0;
}