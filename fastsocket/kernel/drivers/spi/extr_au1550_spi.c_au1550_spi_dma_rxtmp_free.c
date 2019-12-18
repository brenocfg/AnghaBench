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
struct au1550_spi {scalar_t__ dma_rx_tmpbuf_size; scalar_t__ dma_rx_tmpbuf; int /*<<< orphan*/  dma_rx_tmpbuf_addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void au1550_spi_dma_rxtmp_free(struct au1550_spi *hw)
{
	dma_unmap_single(hw->dev, hw->dma_rx_tmpbuf_addr,
			hw->dma_rx_tmpbuf_size, DMA_FROM_DEVICE);
	kfree(hw->dma_rx_tmpbuf);
	hw->dma_rx_tmpbuf = 0;
	hw->dma_rx_tmpbuf_size = 0;
}