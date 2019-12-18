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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_nand_dma_transfer (struct mtd_info*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  omap_read_buf_pref (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void omap_read_buf_dma_pref(struct mtd_info *mtd, u_char *buf, int len)
{
	if (len <= mtd->oobsize)
		omap_read_buf_pref(mtd, buf, len);
	else
		/* start transfer in DMA mode */
		omap_nand_dma_transfer(mtd, buf, len, 0x0);
}