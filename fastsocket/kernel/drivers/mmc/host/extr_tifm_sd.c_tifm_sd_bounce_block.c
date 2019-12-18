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
struct scatterlist {unsigned int length; unsigned int offset; } ;
struct tifm_sd {size_t sg_pos; unsigned int block_pos; size_t sg_len; struct scatterlist bounce_buf; TYPE_1__* dev; } ;
struct page {int dummy; } ;
struct mmc_data {unsigned int blksz; int flags; struct scatterlist* sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct page* nth_page (struct page*,unsigned int) ; 
 unsigned int offset_in_page (unsigned int) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  tifm_sd_copy_page (struct page*,unsigned int,struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static void tifm_sd_bounce_block(struct tifm_sd *host, struct mmc_data *r_data)
{
	struct scatterlist *sg = r_data->sg;
	unsigned int t_size = r_data->blksz;
	unsigned int off, cnt;
	unsigned int p_off, p_cnt;
	struct page *pg;

	dev_dbg(&host->dev->dev, "bouncing block\n");
	while (t_size) {
		cnt = sg[host->sg_pos].length - host->block_pos;
		if (!cnt) {
			host->block_pos = 0;
			host->sg_pos++;
			if (host->sg_pos == host->sg_len)
				return;
			cnt = sg[host->sg_pos].length;
		}
		off = sg[host->sg_pos].offset + host->block_pos;

		pg = nth_page(sg_page(&sg[host->sg_pos]), off >> PAGE_SHIFT);
		p_off = offset_in_page(off);
		p_cnt = PAGE_SIZE - p_off;
		p_cnt = min(p_cnt, cnt);
		p_cnt = min(p_cnt, t_size);

		if (r_data->flags & MMC_DATA_WRITE)
			tifm_sd_copy_page(sg_page(&host->bounce_buf),
					  r_data->blksz - t_size,
					  pg, p_off, p_cnt);
		else if (r_data->flags & MMC_DATA_READ)
			tifm_sd_copy_page(pg, p_off, sg_page(&host->bounce_buf),
					  r_data->blksz - t_size, p_cnt);

		t_size -= p_cnt;
		host->block_pos += p_cnt;
	}
}