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
struct fb_var_screeninfo {int yoffset; int xoffset; int bits_per_pixel; } ;
struct fb_fix_screeninfo {int smem_start; int line_length; } ;
struct fb_info {struct fb_fix_screeninfo fix; struct atmel_lcdfb_info* par; } ;
struct atmel_lcdfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_LCDC_DMABADDR1 ; 
 int /*<<< orphan*/  atmel_lcdfb_update_dma2d (struct atmel_lcdfb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void atmel_lcdfb_update_dma(struct fb_info *info,
			       struct fb_var_screeninfo *var)
{
	struct atmel_lcdfb_info *sinfo = info->par;
	struct fb_fix_screeninfo *fix = &info->fix;
	unsigned long dma_addr;

	dma_addr = (fix->smem_start + var->yoffset * fix->line_length
		    + var->xoffset * var->bits_per_pixel / 8);

	dma_addr &= ~3UL;

	/* Set framebuffer DMA base address and pixel offset */
	lcdc_writel(sinfo, ATMEL_LCDC_DMABADDR1, dma_addr);

	atmel_lcdfb_update_dma2d(sinfo, var);
}