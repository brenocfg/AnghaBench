#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {unsigned int current_dma_page; unsigned int nr_dma_pages; unsigned int first_dma_page; TYPE_2__* dma_pages; TYPE_1__* cmd_dma; int /*<<< orphan*/  last_dma_age; int /*<<< orphan*/  (* dma_flush ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_8__ {unsigned int used; scalar_t__ flushed; int /*<<< orphan*/  age; } ;
struct TYPE_7__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,int) ; 
 unsigned int SAVAGE_DMA_PAGE_SIZE ; 
 int /*<<< orphan*/  savage_dma_wait (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

uint32_t *savage_dma_alloc(drm_savage_private_t * dev_priv, unsigned int n)
{
	unsigned int cur = dev_priv->current_dma_page;
	unsigned int rest = SAVAGE_DMA_PAGE_SIZE -
	    dev_priv->dma_pages[cur].used;
	unsigned int nr_pages = (n - rest + SAVAGE_DMA_PAGE_SIZE - 1) /
	    SAVAGE_DMA_PAGE_SIZE;
	uint32_t *dma_ptr;
	unsigned int i;

	DRM_DEBUG("cur=%u, cur->used=%u, n=%u, rest=%u, nr_pages=%u\n",
		  cur, dev_priv->dma_pages[cur].used, n, rest, nr_pages);

	if (cur + nr_pages < dev_priv->nr_dma_pages) {
		dma_ptr = (uint32_t *) dev_priv->cmd_dma->handle +
		    cur * SAVAGE_DMA_PAGE_SIZE + dev_priv->dma_pages[cur].used;
		if (n < rest)
			rest = n;
		dev_priv->dma_pages[cur].used += rest;
		n -= rest;
		cur++;
	} else {
		dev_priv->dma_flush(dev_priv);
		nr_pages =
		    (n + SAVAGE_DMA_PAGE_SIZE - 1) / SAVAGE_DMA_PAGE_SIZE;
		for (i = cur; i < dev_priv->nr_dma_pages; ++i) {
			dev_priv->dma_pages[i].age = dev_priv->last_dma_age;
			dev_priv->dma_pages[i].used = 0;
			dev_priv->dma_pages[i].flushed = 0;
		}
		dma_ptr = (uint32_t *) dev_priv->cmd_dma->handle;
		dev_priv->first_dma_page = cur = 0;
	}
	for (i = cur; nr_pages > 0; ++i, --nr_pages) {
#if SAVAGE_DMA_DEBUG
		if (dev_priv->dma_pages[i].used) {
			DRM_ERROR("unflushed page %u: used=%u\n",
				  i, dev_priv->dma_pages[i].used);
		}
#endif
		if (n > SAVAGE_DMA_PAGE_SIZE)
			dev_priv->dma_pages[i].used = SAVAGE_DMA_PAGE_SIZE;
		else
			dev_priv->dma_pages[i].used = n;
		n -= SAVAGE_DMA_PAGE_SIZE;
	}
	dev_priv->current_dma_page = --i;

	DRM_DEBUG("cur=%u, cur->used=%u, n=%u\n",
		  i, dev_priv->dma_pages[i].used, n);

	savage_dma_wait(dev_priv, dev_priv->current_dma_page);

	return dma_ptr;
}