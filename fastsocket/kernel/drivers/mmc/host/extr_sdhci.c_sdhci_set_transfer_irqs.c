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
struct sdhci_host {int flags; } ;

/* Variables and functions */
 int SDHCI_INT_ADMA_ERROR ; 
 int SDHCI_INT_DATA_AVAIL ; 
 int SDHCI_INT_DMA_END ; 
 int SDHCI_INT_SPACE_AVAIL ; 
 int SDHCI_REQ_USE_DMA ; 
 int /*<<< orphan*/  sdhci_clear_set_irqs (struct sdhci_host*,int,int) ; 

__attribute__((used)) static void sdhci_set_transfer_irqs(struct sdhci_host *host)
{
	u32 pio_irqs = SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL;
	u32 dma_irqs = SDHCI_INT_DMA_END | SDHCI_INT_ADMA_ERROR;

	if (host->flags & SDHCI_REQ_USE_DMA)
		sdhci_clear_set_irqs(host, pio_irqs, dma_irqs);
	else
		sdhci_clear_set_irqs(host, dma_irqs, pio_irqs);
}