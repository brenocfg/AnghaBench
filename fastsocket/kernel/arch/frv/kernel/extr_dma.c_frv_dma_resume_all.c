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
struct frv_dma_channel {int flags; unsigned long ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCTR ; 
 int /*<<< orphan*/  CSTR ; 
 unsigned long DMAC_CCTRx_ACT ; 
 unsigned long DMAC_CSTRx_FED ; 
 unsigned long DMAC_CSTRx_INT ; 
 int FRV_DMA_FLAGS_PAUSED ; 
 int FRV_DMA_NCHANS ; 
 unsigned long __get_DMAC (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_DMAC (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 struct frv_dma_channel* frv_dma_channels ; 
 int /*<<< orphan*/  frv_dma_channels_lock ; 
 int /*<<< orphan*/  frv_set_dma_inprogress (int) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void frv_dma_resume_all(void)
{
	struct frv_dma_channel *channel;
	unsigned long ioaddr;
	unsigned long cstr, cctr;
	int dma;

	for (dma = FRV_DMA_NCHANS - 1; dma >= 0; dma--) {
		channel = &frv_dma_channels[dma];

		if (!(channel->flags & FRV_DMA_FLAGS_PAUSED))
			continue;

		ioaddr = channel->ioaddr;
		cstr = __get_DMAC(ioaddr, CSTR);
		cstr &= ~(DMAC_CSTRx_FED | DMAC_CSTRx_INT);
		__set_DMAC(ioaddr, CSTR, cstr);

		cctr = __get_DMAC(ioaddr, CCTR);
		cctr |= DMAC_CCTRx_ACT;
		__set_DMAC(ioaddr, CCTR, cctr);

		channel->flags &= ~FRV_DMA_FLAGS_PAUSED;
		frv_set_dma_inprogress(dma);
	}

	write_unlock(&frv_dma_channels_lock);

}