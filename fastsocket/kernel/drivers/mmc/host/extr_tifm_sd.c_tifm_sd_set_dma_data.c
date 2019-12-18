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
struct scatterlist {int dummy; } ;
struct tifm_sd {size_t sg_pos; size_t sg_len; int cmd_flags; unsigned int block_pos; struct scatterlist bounce_buf; struct tifm_dev* dev; } ;
struct tifm_dev {scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct mmc_data {unsigned int blksz; int flags; struct scatterlist* sg; } ;

/* Variables and functions */
 int DATA_CARRY ; 
 int MMC_DATA_WRITE ; 
 scalar_t__ SOCK_DMA_ADDRESS ; 
 scalar_t__ SOCK_DMA_CONTROL ; 
 unsigned int TIFM_DMA_EN ; 
 unsigned int TIFM_DMA_TSIZE ; 
 unsigned int TIFM_DMA_TX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  tifm_sd_bounce_block (struct tifm_sd*,struct mmc_data*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int tifm_sd_set_dma_data(struct tifm_sd *host, struct mmc_data *r_data)
{
	struct tifm_dev *sock = host->dev;
	unsigned int t_size = TIFM_DMA_TSIZE * r_data->blksz;
	unsigned int dma_len, dma_blk_cnt, dma_off;
	struct scatterlist *sg = NULL;
	unsigned long flags;

	if (host->sg_pos == host->sg_len)
		return 1;

	if (host->cmd_flags & DATA_CARRY) {
		host->cmd_flags &= ~DATA_CARRY;
		local_irq_save(flags);
		tifm_sd_bounce_block(host, r_data);
		local_irq_restore(flags);
		if (host->sg_pos == host->sg_len)
			return 1;
	}

	dma_len = sg_dma_len(&r_data->sg[host->sg_pos]) - host->block_pos;
	if (!dma_len) {
		host->block_pos = 0;
		host->sg_pos++;
		if (host->sg_pos == host->sg_len)
			return 1;
		dma_len = sg_dma_len(&r_data->sg[host->sg_pos]);
	}

	if (dma_len < t_size) {
		dma_blk_cnt = dma_len / r_data->blksz;
		dma_off = host->block_pos;
		host->block_pos += dma_blk_cnt * r_data->blksz;
	} else {
		dma_blk_cnt = TIFM_DMA_TSIZE;
		dma_off = host->block_pos;
		host->block_pos += t_size;
	}

	if (dma_blk_cnt)
		sg = &r_data->sg[host->sg_pos];
	else if (dma_len) {
		if (r_data->flags & MMC_DATA_WRITE) {
			local_irq_save(flags);
			tifm_sd_bounce_block(host, r_data);
			local_irq_restore(flags);
		} else
			host->cmd_flags |= DATA_CARRY;

		sg = &host->bounce_buf;
		dma_off = 0;
		dma_blk_cnt = 1;
	} else
		return 1;

	dev_dbg(&sock->dev, "setting dma for %d blocks\n", dma_blk_cnt);
	writel(sg_dma_address(sg) + dma_off, sock->addr + SOCK_DMA_ADDRESS);
	if (r_data->flags & MMC_DATA_WRITE)
		writel((dma_blk_cnt << 8) | TIFM_DMA_TX | TIFM_DMA_EN,
		       sock->addr + SOCK_DMA_CONTROL);
	else
		writel((dma_blk_cnt << 8) | TIFM_DMA_EN,
		       sock->addr + SOCK_DMA_CONTROL);

	return 0;
}