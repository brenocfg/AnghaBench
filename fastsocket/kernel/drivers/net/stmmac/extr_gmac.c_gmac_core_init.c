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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ GMAC_CONTROL ; 
 int GMAC_CORE_INIT ; 
 scalar_t__ GMAC_INT_MASK ; 
 scalar_t__ GMAC_MMC_CTRL ; 
 scalar_t__ GMAC_VLAN_TAG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gmac_core_init(unsigned long ioaddr)
{
	u32 value = readl(ioaddr + GMAC_CONTROL);
	value |= GMAC_CORE_INIT;
	writel(value, ioaddr + GMAC_CONTROL);

	/* STBus Bridge Configuration */
	/*writel(0xc5608, ioaddr + 0x00007000);*/

	/* Freeze MMC counters */
	writel(0x8, ioaddr + GMAC_MMC_CTRL);
	/* Mask GMAC interrupts */
	writel(0x207, ioaddr + GMAC_INT_MASK);

#ifdef STMMAC_VLAN_TAG_USED
	/* Tag detection without filtering */
	writel(0x0, ioaddr + GMAC_VLAN_TAG);
#endif
	return;
}