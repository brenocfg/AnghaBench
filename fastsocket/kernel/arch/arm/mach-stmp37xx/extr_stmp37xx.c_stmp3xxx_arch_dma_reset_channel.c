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
 unsigned int BP_APBH_CTRL0_RESET_CHANNEL ; 
 unsigned int BP_APBX_CTRL0_RESET_CHANNEL ; 
 scalar_t__ HW_APBH_CTRL0 ; 
 scalar_t__ HW_APBX_CTRL0 ; 
 scalar_t__ REGS_APBH_BASE ; 
 scalar_t__ REGS_APBX_BASE ; 
#define  STMP3XXX_BUS_APBH 129 
#define  STMP3XXX_BUS_APBX 128 
 int STMP3XXX_DMA_BUS (int) ; 
 int STMP3XXX_DMA_CHANNEL (int) ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  stmp3xxx_setl (unsigned int,scalar_t__) ; 

void stmp3xxx_arch_dma_reset_channel(int channel)
{
	unsigned chbit = 1 << STMP3XXX_DMA_CHANNEL(channel);

	switch (STMP3XXX_DMA_BUS(channel)) {
	case STMP3XXX_BUS_APBH:
		/* Reset channel and wait for it to complete */
		stmp3xxx_setl(chbit << BP_APBH_CTRL0_RESET_CHANNEL,
			REGS_APBH_BASE + HW_APBH_CTRL0);
		while (__raw_readl(REGS_APBH_BASE + HW_APBH_CTRL0) &
		       (chbit << BP_APBH_CTRL0_RESET_CHANNEL))
				cpu_relax();
		break;

	case STMP3XXX_BUS_APBX:
		stmp3xxx_setl(chbit << BP_APBX_CTRL0_RESET_CHANNEL,
			REGS_APBX_BASE + HW_APBX_CTRL0);
		while (__raw_readl(REGS_APBX_BASE + HW_APBX_CTRL0) &
		       (chbit << BP_APBX_CTRL0_RESET_CHANNEL))
				cpu_relax();
		break;
	}
}