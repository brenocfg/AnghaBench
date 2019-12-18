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
typedef  int /*<<< orphan*/  uint8_t ;
struct mtd_info {int dummy; } ;
struct bf5xx_nand_platform {short page_size; } ;
struct bf5xx_nand_info {int /*<<< orphan*/  dma_completion; int /*<<< orphan*/  device; struct bf5xx_nand_platform* platform; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_NFC ; 
 unsigned short DI_EN ; 
 int /*<<< orphan*/  SSYNC () ; 
 unsigned short WDSIZE_16 ; 
 unsigned short WDSIZE_32 ; 
 unsigned short WNR ; 
 int /*<<< orphan*/  bfin_write_NFC_PGCTL (int) ; 
 int /*<<< orphan*/  bfin_write_NFC_RST (int) ; 
 int /*<<< orphan*/  clear_dma_irqstat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  invalidate_dcache_range (unsigned int,unsigned int) ; 
 struct bf5xx_nand_info* mtd_to_nand_info (struct mtd_info*) ; 
 int /*<<< orphan*/  set_dma_config (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  set_dma_start_addr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_dma_x_count (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  set_dma_x_modify (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bf5xx_nand_dma_rw(struct mtd_info *mtd,
				uint8_t *buf, int is_read)
{
	struct bf5xx_nand_info *info = mtd_to_nand_info(mtd);
	struct bf5xx_nand_platform *plat = info->platform;
	unsigned short page_size = (plat->page_size ? 512 : 256);
	unsigned short val;

	dev_dbg(info->device, " mtd->%p, buf->%p, is_read %d\n",
			mtd, buf, is_read);

	/*
	 * Before starting a dma transfer, be sure to invalidate/flush
	 * the cache over the address range of your DMA buffer to
	 * prevent cache coherency problems. Otherwise very subtle bugs
	 * can be introduced to your driver.
	 */
	if (is_read)
		invalidate_dcache_range((unsigned int)buf,
				(unsigned int)(buf + page_size));
	else
		flush_dcache_range((unsigned int)buf,
				(unsigned int)(buf + page_size));

	/*
	 * This register must be written before each page is
	 * transferred to generate the correct ECC register
	 * values.
	 */
	bfin_write_NFC_RST(0x1);
	SSYNC();

	disable_dma(CH_NFC);
	clear_dma_irqstat(CH_NFC);

	/* setup DMA register with Blackfin DMA API */
	set_dma_config(CH_NFC, 0x0);
	set_dma_start_addr(CH_NFC, (unsigned long) buf);

/* The DMAs have different size on BF52x and BF54x */
#ifdef CONFIG_BF52x
	set_dma_x_count(CH_NFC, (page_size >> 1));
	set_dma_x_modify(CH_NFC, 2);
	val = DI_EN | WDSIZE_16;
#endif

#ifdef CONFIG_BF54x
	set_dma_x_count(CH_NFC, (page_size >> 2));
	set_dma_x_modify(CH_NFC, 4);
	val = DI_EN | WDSIZE_32;
#endif
	/* setup write or read operation */
	if (is_read)
		val |= WNR;
	set_dma_config(CH_NFC, val);
	enable_dma(CH_NFC);

	/* Start PAGE read/write operation */
	if (is_read)
		bfin_write_NFC_PGCTL(0x1);
	else
		bfin_write_NFC_PGCTL(0x2);
	wait_for_completion(&info->dma_completion);
}