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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct spi_transfer {unsigned int len; unsigned long tx_dma; unsigned long rx_dma; void** rx_buf; void** tx_buf; } ;
struct spi_device {size_t chip_select; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; struct omap2_mcspi_cs* controller_state; } ;
struct omap2_mcspi_dma {int /*<<< orphan*/  dma_rx_completion; int /*<<< orphan*/  dma_tx_completion; int /*<<< orphan*/  dma_rx_channel; int /*<<< orphan*/  dma_tx_channel; int /*<<< orphan*/  dma_rx_sync_dev; int /*<<< orphan*/  dma_tx_sync_dev; } ;
struct omap2_mcspi_cs {int word_len; unsigned long phys; } ;
struct omap2_mcspi {struct omap2_mcspi_dma* dma_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned long OMAP2_MCSPI_CHSTAT0 ; 
 int OMAP2_MCSPI_CHSTAT_RXS ; 
 unsigned long OMAP2_MCSPI_RX0 ; 
 unsigned long OMAP2_MCSPI_TX0 ; 
 int /*<<< orphan*/  OMAP_DMA_AMODE_CONSTANT ; 
 int /*<<< orphan*/  OMAP_DMA_AMODE_POST_INC ; 
 int OMAP_DMA_DATA_TYPE_S16 ; 
 int OMAP_DMA_DATA_TYPE_S32 ; 
 int OMAP_DMA_DATA_TYPE_S8 ; 
 int /*<<< orphan*/  OMAP_DMA_SYNC_ELEMENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int mcspi_read_cs_reg (struct spi_device*,unsigned long) ; 
 int /*<<< orphan*/  omap2_mcspi_set_dma_req (struct spi_device*,int,int) ; 
 int /*<<< orphan*/  omap2_mcspi_set_enable (struct spi_device*,int) ; 
 int /*<<< orphan*/  omap_set_dma_dest_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_src_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_transfer_params (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_start_dma (int /*<<< orphan*/ ) ; 
 struct omap2_mcspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned
omap2_mcspi_txrx_dma(struct spi_device *spi, struct spi_transfer *xfer)
{
	struct omap2_mcspi	*mcspi;
	struct omap2_mcspi_cs	*cs = spi->controller_state;
	struct omap2_mcspi_dma  *mcspi_dma;
	unsigned int		count, c;
	unsigned long		base, tx_reg, rx_reg;
	int			word_len, data_type, element_count;
	u8			* rx;
	const u8		* tx;

	mcspi = spi_master_get_devdata(spi->master);
	mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	count = xfer->len;
	c = count;
	word_len = cs->word_len;

	base = cs->phys;
	tx_reg = base + OMAP2_MCSPI_TX0;
	rx_reg = base + OMAP2_MCSPI_RX0;
	rx = xfer->rx_buf;
	tx = xfer->tx_buf;

	if (word_len <= 8) {
		data_type = OMAP_DMA_DATA_TYPE_S8;
		element_count = count;
	} else if (word_len <= 16) {
		data_type = OMAP_DMA_DATA_TYPE_S16;
		element_count = count >> 1;
	} else /* word_len <= 32 */ {
		data_type = OMAP_DMA_DATA_TYPE_S32;
		element_count = count >> 2;
	}

	if (tx != NULL) {
		omap_set_dma_transfer_params(mcspi_dma->dma_tx_channel,
				data_type, element_count, 1,
				OMAP_DMA_SYNC_ELEMENT,
				mcspi_dma->dma_tx_sync_dev, 0);

		omap_set_dma_dest_params(mcspi_dma->dma_tx_channel, 0,
				OMAP_DMA_AMODE_CONSTANT,
				tx_reg, 0, 0);

		omap_set_dma_src_params(mcspi_dma->dma_tx_channel, 0,
				OMAP_DMA_AMODE_POST_INC,
				xfer->tx_dma, 0, 0);
	}

	if (rx != NULL) {
		omap_set_dma_transfer_params(mcspi_dma->dma_rx_channel,
				data_type, element_count - 1, 1,
				OMAP_DMA_SYNC_ELEMENT,
				mcspi_dma->dma_rx_sync_dev, 1);

		omap_set_dma_src_params(mcspi_dma->dma_rx_channel, 0,
				OMAP_DMA_AMODE_CONSTANT,
				rx_reg, 0, 0);

		omap_set_dma_dest_params(mcspi_dma->dma_rx_channel, 0,
				OMAP_DMA_AMODE_POST_INC,
				xfer->rx_dma, 0, 0);
	}

	if (tx != NULL) {
		omap_start_dma(mcspi_dma->dma_tx_channel);
		omap2_mcspi_set_dma_req(spi, 0, 1);
	}

	if (rx != NULL) {
		omap_start_dma(mcspi_dma->dma_rx_channel);
		omap2_mcspi_set_dma_req(spi, 1, 1);
	}

	if (tx != NULL) {
		wait_for_completion(&mcspi_dma->dma_tx_completion);
		dma_unmap_single(NULL, xfer->tx_dma, count, DMA_TO_DEVICE);
	}

	if (rx != NULL) {
		wait_for_completion(&mcspi_dma->dma_rx_completion);
		dma_unmap_single(NULL, xfer->rx_dma, count, DMA_FROM_DEVICE);
		omap2_mcspi_set_enable(spi, 0);
		if (likely(mcspi_read_cs_reg(spi, OMAP2_MCSPI_CHSTAT0)
				& OMAP2_MCSPI_CHSTAT_RXS)) {
			u32 w;

			w = mcspi_read_cs_reg(spi, OMAP2_MCSPI_RX0);
			if (word_len <= 8)
				((u8 *)xfer->rx_buf)[element_count - 1] = w;
			else if (word_len <= 16)
				((u16 *)xfer->rx_buf)[element_count - 1] = w;
			else /* word_len <= 32 */
				((u32 *)xfer->rx_buf)[element_count - 1] = w;
		} else {
			dev_err(&spi->dev, "DMA RX last word empty");
			count -= (word_len <= 8)  ? 1 :
				 (word_len <= 16) ? 2 :
			       /* word_len <= 32 */ 4;
		}
		omap2_mcspi_set_enable(spi, 1);
	}
	return count;
}