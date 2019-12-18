#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct spi_transfer {scalar_t__ len; scalar_t__ tx_dma; scalar_t__ rx_dma; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct au1550_spi {scalar_t__ len; scalar_t__ tx_count; scalar_t__ rx_count; scalar_t__ dma_rx_tmpbuf_size; scalar_t__ dma_rx_tmpbuf_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_rx_ch; int /*<<< orphan*/  dma_tx_ch; int /*<<< orphan*/  master_done; TYPE_1__* regs; scalar_t__ tx; scalar_t__ rx; scalar_t__ dma_rx_tmpbuf; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  psc_spipcr; int /*<<< orphan*/  psc_spimsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1550_SPI_DMA_RXTMP_MINSIZE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PSC_SPIMSK_SD ; 
 int /*<<< orphan*/  PSC_SPIPCR_MS ; 
 int au1550_spi_dma_rxtmp_alloc (struct au1550_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1550_spi_dma_rxtmp_free (struct au1550_spi*) ; 
 scalar_t__ au1xxx_dbdma_put_dest (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ au1xxx_dbdma_put_source (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  au1xxx_dbdma_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 struct au1550_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int au1550_spi_dma_txrxb(struct spi_device *spi, struct spi_transfer *t)
{
	struct au1550_spi *hw = spi_master_get_devdata(spi->master);
	dma_addr_t dma_tx_addr;
	dma_addr_t dma_rx_addr;
	u32 res;

	hw->len = t->len;
	hw->tx_count = 0;
	hw->rx_count = 0;

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	dma_tx_addr = t->tx_dma;
	dma_rx_addr = t->rx_dma;

	/*
	 * check if buffers are already dma mapped, map them otherwise:
	 * - first map the TX buffer, so cache data gets written to memory
	 * - then map the RX buffer, so that cache entries (with
	 *   soon-to-be-stale data) get removed
	 * use rx buffer in place of tx if tx buffer was not provided
	 * use temp rx buffer (preallocated or realloc to fit) for rx dma
	 */
	if (t->tx_buf) {
		if (t->tx_dma == 0) {	/* if DMA_ADDR_INVALID, map it */
			dma_tx_addr = dma_map_single(hw->dev,
					(void *)t->tx_buf,
					t->len, DMA_TO_DEVICE);
			if (dma_mapping_error(hw->dev, dma_tx_addr))
				dev_err(hw->dev, "tx dma map error\n");
		}
	}

	if (t->rx_buf) {
		if (t->rx_dma == 0) {	/* if DMA_ADDR_INVALID, map it */
			dma_rx_addr = dma_map_single(hw->dev,
					(void *)t->rx_buf,
					t->len, DMA_FROM_DEVICE);
			if (dma_mapping_error(hw->dev, dma_rx_addr))
				dev_err(hw->dev, "rx dma map error\n");
		}
	} else {
		if (t->len > hw->dma_rx_tmpbuf_size) {
			int ret;

			au1550_spi_dma_rxtmp_free(hw);
			ret = au1550_spi_dma_rxtmp_alloc(hw, max(t->len,
					AU1550_SPI_DMA_RXTMP_MINSIZE));
			if (ret < 0)
				return ret;
		}
		hw->rx = hw->dma_rx_tmpbuf;
		dma_rx_addr = hw->dma_rx_tmpbuf_addr;
		dma_sync_single_for_device(hw->dev, dma_rx_addr,
			t->len, DMA_FROM_DEVICE);
	}

	if (!t->tx_buf) {
		dma_sync_single_for_device(hw->dev, dma_rx_addr,
				t->len, DMA_BIDIRECTIONAL);
		hw->tx = hw->rx;
	}

	/* put buffers on the ring */
	res = au1xxx_dbdma_put_dest(hw->dma_rx_ch, hw->rx, t->len);
	if (!res)
		dev_err(hw->dev, "rx dma put dest error\n");

	res = au1xxx_dbdma_put_source(hw->dma_tx_ch, (void *)hw->tx, t->len);
	if (!res)
		dev_err(hw->dev, "tx dma put source error\n");

	au1xxx_dbdma_start(hw->dma_rx_ch);
	au1xxx_dbdma_start(hw->dma_tx_ch);

	/* by default enable nearly all events interrupt */
	hw->regs->psc_spimsk = PSC_SPIMSK_SD;
	au_sync();

	/* start the transfer */
	hw->regs->psc_spipcr = PSC_SPIPCR_MS;
	au_sync();

	wait_for_completion(&hw->master_done);

	au1xxx_dbdma_stop(hw->dma_tx_ch);
	au1xxx_dbdma_stop(hw->dma_rx_ch);

	if (!t->rx_buf) {
		/* using the temporal preallocated and premapped buffer */
		dma_sync_single_for_cpu(hw->dev, dma_rx_addr, t->len,
			DMA_FROM_DEVICE);
	}
	/* unmap buffers if mapped above */
	if (t->rx_buf && t->rx_dma == 0 )
		dma_unmap_single(hw->dev, dma_rx_addr, t->len,
			DMA_FROM_DEVICE);
	if (t->tx_buf && t->tx_dma == 0 )
		dma_unmap_single(hw->dev, dma_tx_addr, t->len,
			DMA_TO_DEVICE);

	return hw->rx_count < hw->tx_count ? hw->rx_count : hw->tx_count;
}