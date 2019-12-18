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
struct stmmac_extra_stats {int rx_overflow_cntr; int rx_missed_cntr; } ;
struct net_device_stats {int rx_over_errors; int rx_missed_errors; } ;

/* Variables and functions */
 scalar_t__ DMA_MISSED_FRAME_CTR ; 
 int DMA_MISSED_FRAME_M_CNTR ; 
 int DMA_MISSED_FRAME_OVE ; 
 int DMA_MISSED_FRAME_OVE_CNTR ; 
 int DMA_MISSED_FRAME_OVE_M ; 
 int readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mac100_dma_diagnostic_fr(void *data, struct stmmac_extra_stats *x,
				     unsigned long ioaddr)
{
	struct net_device_stats *stats = (struct net_device_stats *)data;
	u32 csr8 = readl(ioaddr + DMA_MISSED_FRAME_CTR);

	if (unlikely(csr8)) {
		if (csr8 & DMA_MISSED_FRAME_OVE) {
			stats->rx_over_errors += 0x800;
			x->rx_overflow_cntr += 0x800;
		} else {
			unsigned int ove_cntr;
			ove_cntr = ((csr8 & DMA_MISSED_FRAME_OVE_CNTR) >> 17);
			stats->rx_over_errors += ove_cntr;
			x->rx_overflow_cntr += ove_cntr;
		}

		if (csr8 & DMA_MISSED_FRAME_OVE_M) {
			stats->rx_missed_errors += 0xffff;
			x->rx_missed_cntr += 0xffff;
		} else {
			unsigned int miss_f = (csr8 & DMA_MISSED_FRAME_M_CNTR);
			stats->rx_missed_errors += miss_f;
			x->rx_missed_cntr += miss_f;
		}
	}
	return;
}