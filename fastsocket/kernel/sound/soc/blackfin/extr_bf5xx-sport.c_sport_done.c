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
struct sport_device {int rx_desc_bytes; int tx_desc_bytes; int /*<<< orphan*/  err_irq; int /*<<< orphan*/  dma_tx_chan; int /*<<< orphan*/  dma_rx_chan; struct sport_device* dummy_buf; struct sport_device* dummy_tx_desc; struct sport_device* dummy_rx_desc; struct sport_device* dma_tx_desc; struct sport_device* dma_rx_desc; } ;
struct dmasg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct sport_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sport_device*) ; 
 int /*<<< orphan*/  kfree (struct sport_device*) ; 
 int /*<<< orphan*/  l1_data_sram_free (struct sport_device*) ; 
 int /*<<< orphan*/  sport_stop (struct sport_device*) ; 

void sport_done(struct sport_device *sport)
{
	if (sport == NULL)
		return;

	sport_stop(sport);
	if (sport->dma_rx_desc)
		dma_free_coherent(NULL, sport->rx_desc_bytes,
			sport->dma_rx_desc, 0);
	if (sport->dma_tx_desc)
		dma_free_coherent(NULL, sport->tx_desc_bytes,
			sport->dma_tx_desc, 0);

#if L1_DATA_A_LENGTH != 0
	l1_data_sram_free(sport->dummy_rx_desc);
	l1_data_sram_free(sport->dummy_tx_desc);
	l1_data_sram_free(sport->dummy_buf);
#else
	dma_free_coherent(NULL, 2*sizeof(struct dmasg),
		sport->dummy_rx_desc, 0);
	dma_free_coherent(NULL, 2*sizeof(struct dmasg),
		sport->dummy_tx_desc, 0);
	kfree(sport->dummy_buf);
#endif
	free_dma(sport->dma_rx_chan);
	free_dma(sport->dma_tx_chan);
	free_irq(sport->err_irq, sport);

	kfree(sport);
		sport = NULL;
}