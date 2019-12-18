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
struct b43_dmaring {scalar_t__ type; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  dev; scalar_t__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DMA32_RXRING ; 
 int /*<<< orphan*/  B43_DMA32_TXRING ; 
 int /*<<< orphan*/  B43_DMA64_RXRINGHI ; 
 int /*<<< orphan*/  B43_DMA64_RXRINGLO ; 
 int /*<<< orphan*/  B43_DMA64_TXRINGHI ; 
 int /*<<< orphan*/  B43_DMA64_TXRINGLO ; 
 scalar_t__ B43_DMA_64BIT ; 
 int /*<<< orphan*/  b43_dma_write (struct b43_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dmacontroller_rx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  b43_dmacontroller_tx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dmacontroller_cleanup(struct b43_dmaring *ring)
{
	if (ring->tx) {
		b43_dmacontroller_tx_reset(ring->dev, ring->mmio_base,
					   ring->type);
		if (ring->type == B43_DMA_64BIT) {
			b43_dma_write(ring, B43_DMA64_TXRINGLO, 0);
			b43_dma_write(ring, B43_DMA64_TXRINGHI, 0);
		} else
			b43_dma_write(ring, B43_DMA32_TXRING, 0);
	} else {
		b43_dmacontroller_rx_reset(ring->dev, ring->mmio_base,
					   ring->type);
		if (ring->type == B43_DMA_64BIT) {
			b43_dma_write(ring, B43_DMA64_RXRINGLO, 0);
			b43_dma_write(ring, B43_DMA64_RXRINGHI, 0);
		} else
			b43_dma_write(ring, B43_DMA32_RXRING, 0);
	}
}