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
 int BM_APBH_CHn_SEMA_PHORE ; 
 int BM_APBX_CHn_SEMA_PHORE ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HW_APBH_CHn_SEMA ; 
 scalar_t__ HW_APBX_CHn_SEMA ; 
 scalar_t__ REGS_APBH_BASE ; 
 scalar_t__ REGS_APBX_BASE ; 
#define  STMP3XXX_BUS_APBH 129 
#define  STMP3XXX_BUS_APBX 128 
 int STMP3XXX_DMA_BUS (int) ; 
 int STMP3XXX_DMA_CHANNEL (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

int stmp3xxx_dma_running(int channel)
{
	switch (STMP3XXX_DMA_BUS(channel)) {
	case STMP3XXX_BUS_APBH:
		return (__raw_readl(REGS_APBH_BASE + HW_APBH_CHn_SEMA +
			0x70 * STMP3XXX_DMA_CHANNEL(channel))) &
			    BM_APBH_CHn_SEMA_PHORE;

	case STMP3XXX_BUS_APBX:
		return (__raw_readl(REGS_APBX_BASE + HW_APBX_CHn_SEMA +
			0x70 * STMP3XXX_DMA_CHANNEL(channel))) &
			    BM_APBX_CHn_SEMA_PHORE;
	default:
		BUG();
		return 0;
	}
}