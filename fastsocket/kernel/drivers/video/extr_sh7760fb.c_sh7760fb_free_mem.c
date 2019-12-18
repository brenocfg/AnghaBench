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
struct sh7760fb_par {scalar_t__ fbdma; } ;
struct fb_info {scalar_t__ screen_size; int /*<<< orphan*/ * screen_base; int /*<<< orphan*/  dev; struct sh7760fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sh7760fb_free_mem(struct fb_info *info)
{
	struct sh7760fb_par *par = info->par;

	if (!info->screen_base)
		return;

	dma_free_coherent(info->dev, info->screen_size,
			  info->screen_base, par->fbdma);

	par->fbdma = 0;
	info->screen_base = NULL;
	info->screen_size = 0;
}