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
struct spi_master {int dummy; } ;
struct spi_device {int chip_select; int /*<<< orphan*/  dev; struct spi_master* master; } ;
struct omap2_mcspi_dma {int dma_rx_channel; int dma_tx_channel; int /*<<< orphan*/  dma_tx_completion; int /*<<< orphan*/  dma_rx_completion; int /*<<< orphan*/  dma_tx_sync_dev; int /*<<< orphan*/  dma_rx_sync_dev; } ;
struct omap2_mcspi {struct omap2_mcspi_dma* dma_channels; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap2_mcspi_dma_rx_callback ; 
 int /*<<< orphan*/  omap2_mcspi_dma_tx_callback ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 
 scalar_t__ omap_request_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct spi_device*,int*) ; 
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int omap2_mcspi_request_dma(struct spi_device *spi)
{
	struct spi_master	*master = spi->master;
	struct omap2_mcspi	*mcspi;
	struct omap2_mcspi_dma	*mcspi_dma;

	mcspi = spi_master_get_devdata(master);
	mcspi_dma = mcspi->dma_channels + spi->chip_select;

	if (omap_request_dma(mcspi_dma->dma_rx_sync_dev, "McSPI RX",
			omap2_mcspi_dma_rx_callback, spi,
			&mcspi_dma->dma_rx_channel)) {
		dev_err(&spi->dev, "no RX DMA channel for McSPI\n");
		return -EAGAIN;
	}

	if (omap_request_dma(mcspi_dma->dma_tx_sync_dev, "McSPI TX",
			omap2_mcspi_dma_tx_callback, spi,
			&mcspi_dma->dma_tx_channel)) {
		omap_free_dma(mcspi_dma->dma_rx_channel);
		mcspi_dma->dma_rx_channel = -1;
		dev_err(&spi->dev, "no TX DMA channel for McSPI\n");
		return -EAGAIN;
	}

	init_completion(&mcspi_dma->dma_rx_completion);
	init_completion(&mcspi_dma->dma_tx_completion);

	return 0;
}