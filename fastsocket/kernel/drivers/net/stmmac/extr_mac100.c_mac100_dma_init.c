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
 scalar_t__ DMA_BUS_MODE ; 
 int DMA_BUS_MODE_DEFAULT ; 
 int DMA_BUS_MODE_PBL_SHIFT ; 
 int DMA_BUS_MODE_SFT_RESET ; 
 int DMA_INTR_DEFAULT_MASK ; 
 scalar_t__ DMA_INTR_ENA ; 
 scalar_t__ DMA_RCV_BASE_ADDR ; 
 scalar_t__ DMA_TX_BASE_ADDR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mac100_dma_init(unsigned long ioaddr, int pbl, u32 dma_tx,
			   u32 dma_rx)
{
	u32 value = readl(ioaddr + DMA_BUS_MODE);
	/* DMA SW reset */
	value |= DMA_BUS_MODE_SFT_RESET;
	writel(value, ioaddr + DMA_BUS_MODE);
	do {} while ((readl(ioaddr + DMA_BUS_MODE) & DMA_BUS_MODE_SFT_RESET));

	/* Enable Application Access by writing to DMA CSR0 */
	writel(DMA_BUS_MODE_DEFAULT | (pbl << DMA_BUS_MODE_PBL_SHIFT),
	       ioaddr + DMA_BUS_MODE);

	/* Mask interrupts by writing to CSR7 */
	writel(DMA_INTR_DEFAULT_MASK, ioaddr + DMA_INTR_ENA);

	/* The base address of the RX/TX descriptor lists must be written into
	 * DMA CSR3 and CSR4, respectively. */
	writel(dma_tx, ioaddr + DMA_TX_BASE_ADDR);
	writel(dma_rx, ioaddr + DMA_RCV_BASE_ADDR);

	return 0;
}