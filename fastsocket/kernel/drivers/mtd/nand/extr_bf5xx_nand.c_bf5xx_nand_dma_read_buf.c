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
struct bf5xx_nand_info {int /*<<< orphan*/  device; struct bf5xx_nand_platform* platform; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf5xx_nand_dma_rw (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bf5xx_nand_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 struct bf5xx_nand_info* mtd_to_nand_info (struct mtd_info*) ; 

__attribute__((used)) static void bf5xx_nand_dma_read_buf(struct mtd_info *mtd,
					uint8_t *buf, int len)
{
	struct bf5xx_nand_info *info = mtd_to_nand_info(mtd);
	struct bf5xx_nand_platform *plat = info->platform;
	unsigned short page_size = (plat->page_size ? 512 : 256);

	dev_dbg(info->device, "mtd->%p, buf->%p, int %d\n", mtd, buf, len);

	if (len == page_size)
		bf5xx_nand_dma_rw(mtd, buf, 1);
	else
		bf5xx_nand_read_buf(mtd, buf, len);
}