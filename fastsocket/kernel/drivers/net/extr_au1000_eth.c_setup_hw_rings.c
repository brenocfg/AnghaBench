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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tx_dma_t ;
struct au1000_private {int /*<<< orphan*/  volatile** tx_dma_ring; int /*<<< orphan*/  volatile** rx_dma_ring; } ;
typedef  int /*<<< orphan*/  rx_dma_t ;

/* Variables and functions */
 int NUM_RX_DMA ; 
 int NUM_TX_DMA ; 

__attribute__((used)) static void
setup_hw_rings(struct au1000_private *aup, u32 rx_base, u32 tx_base)
{
	int i;

	for (i = 0; i < NUM_RX_DMA; i++) {
		aup->rx_dma_ring[i] =
			(volatile rx_dma_t *) (rx_base + sizeof(rx_dma_t)*i);
	}
	for (i = 0; i < NUM_TX_DMA; i++) {
		aup->tx_dma_ring[i] =
			(volatile tx_dma_t *) (tx_base + sizeof(tx_dma_t)*i);
	}
}