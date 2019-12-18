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
struct videobuf_dmabuf {int direction; int nr_pages; int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned long,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vmalloc_32 (int) ; 

int videobuf_dma_init_kernel(struct videobuf_dmabuf *dma, int direction,
			     int nr_pages)
{
	dprintk(1, "init kernel [%d pages]\n", nr_pages);

	dma->direction = direction;
	dma->vaddr = vmalloc_32(nr_pages << PAGE_SHIFT);
	if (NULL == dma->vaddr) {
		dprintk(1, "vmalloc_32(%d pages) failed\n", nr_pages);
		return -ENOMEM;
	}

	dprintk(1, "vmalloc is at addr 0x%08lx, size=%d\n",
				(unsigned long)dma->vaddr,
				nr_pages << PAGE_SHIFT);

	memset(dma->vaddr, 0, nr_pages << PAGE_SHIFT);
	dma->nr_pages = nr_pages;

	return 0;
}