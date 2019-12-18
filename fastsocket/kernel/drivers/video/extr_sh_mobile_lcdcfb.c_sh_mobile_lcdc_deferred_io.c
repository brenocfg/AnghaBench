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
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  sglist; int /*<<< orphan*/  lcdc; } ;
struct list_head {int dummy; } ;
struct fb_info {int /*<<< orphan*/  dev; struct sh_mobile_lcdc_chan* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  LDSM2R ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write_chan (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_on (int /*<<< orphan*/ ) ; 
 unsigned int sh_mobile_lcdc_sginit (struct fb_info*,struct list_head*) ; 

__attribute__((used)) static void sh_mobile_lcdc_deferred_io(struct fb_info *info,
				       struct list_head *pagelist)
{
	struct sh_mobile_lcdc_chan *ch = info->par;
	unsigned int nr_pages;

	/* enable clocks before accessing hardware */
	sh_mobile_lcdc_clk_on(ch->lcdc);

	nr_pages = sh_mobile_lcdc_sginit(info, pagelist);
	dma_map_sg(info->dev, ch->sglist, nr_pages, DMA_TO_DEVICE);

	/* trigger panel update */
	lcdc_write_chan(ch, LDSM2R, 1);

	dma_unmap_sg(info->dev, ch->sglist, nr_pages, DMA_TO_DEVICE);
}