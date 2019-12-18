#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spi_transfer {int speed_hz; unsigned int len; void* rx_buf; void* tx_buf; void* rx_dma; void* tx_dma; } ;
struct spi_device {int max_speed_hz; int /*<<< orphan*/  dev; } ;
struct scratch {scalar_t__* status; } ;
struct scatterlist {unsigned int length; scalar_t__ offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfers; } ;
struct TYPE_3__ {unsigned int len; int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  transfer_list; } ;
struct mmc_spi_host {int /*<<< orphan*/  data_dma; struct device* dma_dev; TYPE_2__ m; TYPE_1__ early_status; struct scratch* data; struct spi_device* spi; struct spi_transfer t; } ;
struct mmc_data {int blocks; int flags; int timeout_ns; int timeout_clks; unsigned int sg_len; unsigned int bytes_xfered; int error; struct scatterlist* sg; } ;
struct mmc_command {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MMC_DATA_READ ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ SPI_TOKEN_STOP_TRAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 void* dma_map_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,void*,unsigned int,int) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page (int /*<<< orphan*/ ) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,unsigned int const) ; 
 unsigned int min (unsigned int,int) ; 
 int mmc_spi_readblock (struct mmc_spi_host*,struct spi_transfer*,unsigned long) ; 
 int /*<<< orphan*/  mmc_spi_setup_data_message (struct mmc_spi_host*,int,int) ; 
 int mmc_spi_wait_unbusy (struct mmc_spi_host*,unsigned long) ; 
 int mmc_spi_writeblock (struct mmc_spi_host*,struct spi_transfer*,unsigned long) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int spi_sync (struct spi_device*,TYPE_2__*) ; 
 int usecs_to_jiffies (unsigned int) ; 

__attribute__((used)) static void
mmc_spi_data_do(struct mmc_spi_host *host, struct mmc_command *cmd,
		struct mmc_data *data, u32 blk_size)
{
	struct spi_device	*spi = host->spi;
	struct device		*dma_dev = host->dma_dev;
	struct spi_transfer	*t;
	enum dma_data_direction	direction;
	struct scatterlist	*sg;
	unsigned		n_sg;
	int			multiple = (data->blocks > 1);
	u32			clock_rate;
	unsigned long		timeout;

	if (data->flags & MMC_DATA_READ)
		direction = DMA_FROM_DEVICE;
	else
		direction = DMA_TO_DEVICE;
	mmc_spi_setup_data_message(host, multiple, direction);
	t = &host->t;

	if (t->speed_hz)
		clock_rate = t->speed_hz;
	else
		clock_rate = spi->max_speed_hz;

	timeout = data->timeout_ns +
		  data->timeout_clks * 1000000 / clock_rate;
	timeout = usecs_to_jiffies((unsigned int)(timeout / 1000)) + 1;

	/* Handle scatterlist segments one at a time, with synch for
	 * each 512-byte block
	 */
	for (sg = data->sg, n_sg = data->sg_len; n_sg; n_sg--, sg++) {
		int			status = 0;
		dma_addr_t		dma_addr = 0;
		void			*kmap_addr;
		unsigned		length = sg->length;
		enum dma_data_direction	dir = direction;

		/* set up dma mapping for controller drivers that might
		 * use DMA ... though they may fall back to PIO
		 */
		if (dma_dev) {
			/* never invalidate whole *shared* pages ... */
			if ((sg->offset != 0 || length != PAGE_SIZE)
					&& dir == DMA_FROM_DEVICE)
				dir = DMA_BIDIRECTIONAL;

			dma_addr = dma_map_page(dma_dev, sg_page(sg), 0,
						PAGE_SIZE, dir);
			if (direction == DMA_TO_DEVICE)
				t->tx_dma = dma_addr + sg->offset;
			else
				t->rx_dma = dma_addr + sg->offset;
		}

		/* allow pio too; we don't allow highmem */
		kmap_addr = kmap(sg_page(sg));
		if (direction == DMA_TO_DEVICE)
			t->tx_buf = kmap_addr + sg->offset;
		else
			t->rx_buf = kmap_addr + sg->offset;

		/* transfer each block, and update request status */
		while (length) {
			t->len = min(length, blk_size);

			dev_dbg(&host->spi->dev,
				"    mmc_spi: %s block, %d bytes\n",
				(direction == DMA_TO_DEVICE)
				? "write"
				: "read",
				t->len);

			if (direction == DMA_TO_DEVICE)
				status = mmc_spi_writeblock(host, t, timeout);
			else
				status = mmc_spi_readblock(host, t, timeout);
			if (status < 0)
				break;

			data->bytes_xfered += t->len;
			length -= t->len;

			if (!multiple)
				break;
		}

		/* discard mappings */
		if (direction == DMA_FROM_DEVICE)
			flush_kernel_dcache_page(sg_page(sg));
		kunmap(sg_page(sg));
		if (dma_dev)
			dma_unmap_page(dma_dev, dma_addr, PAGE_SIZE, dir);

		if (status < 0) {
			data->error = status;
			dev_dbg(&spi->dev, "%s status %d\n",
				(direction == DMA_TO_DEVICE)
					? "write" : "read",
				status);
			break;
		}
	}

	/* NOTE some docs describe an MMC-only SET_BLOCK_COUNT (CMD23) that
	 * can be issued before multiblock writes.  Unlike its more widely
	 * documented analogue for SD cards (SET_WR_BLK_ERASE_COUNT, ACMD23),
	 * that can affect the STOP_TRAN logic.   Complete (and current)
	 * MMC specs should sort that out before Linux starts using CMD23.
	 */
	if (direction == DMA_TO_DEVICE && multiple) {
		struct scratch	*scratch = host->data;
		int		tmp;
		const unsigned	statlen = sizeof(scratch->status);

		dev_dbg(&spi->dev, "    mmc_spi: STOP_TRAN\n");

		/* Tweak the per-block message we set up earlier by morphing
		 * it to hold single buffer with the token followed by some
		 * all-ones bytes ... skip N(BR) (0..1), scan the rest for
		 * "not busy any longer" status, and leave chip selected.
		 */
		INIT_LIST_HEAD(&host->m.transfers);
		list_add(&host->early_status.transfer_list,
				&host->m.transfers);

		memset(scratch->status, 0xff, statlen);
		scratch->status[0] = SPI_TOKEN_STOP_TRAN;

		host->early_status.tx_buf = host->early_status.rx_buf;
		host->early_status.tx_dma = host->early_status.rx_dma;
		host->early_status.len = statlen;

		if (host->dma_dev)
			dma_sync_single_for_device(host->dma_dev,
					host->data_dma, sizeof(*scratch),
					DMA_BIDIRECTIONAL);

		tmp = spi_sync(spi, &host->m);

		if (host->dma_dev)
			dma_sync_single_for_cpu(host->dma_dev,
					host->data_dma, sizeof(*scratch),
					DMA_BIDIRECTIONAL);

		if (tmp < 0) {
			if (!data->error)
				data->error = tmp;
			return;
		}

		/* Ideally we collected "not busy" status with one I/O,
		 * avoiding wasteful byte-at-a-time scanning... but more
		 * I/O is often needed.
		 */
		for (tmp = 2; tmp < statlen; tmp++) {
			if (scratch->status[tmp] != 0)
				return;
		}
		tmp = mmc_spi_wait_unbusy(host, timeout);
		if (tmp < 0 && !data->error)
			data->error = tmp;
	}
}