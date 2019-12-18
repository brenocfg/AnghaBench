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
 scalar_t__ HW_APBH_CTRL0 ; 
 scalar_t__ HW_APBX_CHANNEL_CTRL ; 
 scalar_t__ REGS_APBH_BASE ; 
 scalar_t__ REGS_APBX_BASE ; 
#define  STMP3XXX_BUS_APBH 129 
#define  STMP3XXX_BUS_APBX 128 
 int STMP3XXX_DMA_BUS (int) ; 
 int STMP3XXX_DMA_CHANNEL (int) ; 
 int /*<<< orphan*/  stmp3xxx_setl (int,scalar_t__) ; 

void stmp3xxx_arch_dma_freeze(int channel)
{
	unsigned chbit = 1 << STMP3XXX_DMA_CHANNEL(channel);
	u32 mask = 1 << chbit;

	switch (STMP3XXX_DMA_BUS(channel)) {
	case STMP3XXX_BUS_APBH:
		stmp3xxx_setl(mask, REGS_APBH_BASE + HW_APBH_CTRL0);
		break;
	case STMP3XXX_BUS_APBX:
		stmp3xxx_setl(mask, REGS_APBX_BASE + HW_APBX_CHANNEL_CTRL);
		break;
	}
}