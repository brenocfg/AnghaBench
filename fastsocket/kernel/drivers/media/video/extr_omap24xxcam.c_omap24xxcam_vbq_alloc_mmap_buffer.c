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
struct videobuf_dmabuf {int /*<<< orphan*/  direction; scalar_t__ sglen; scalar_t__ nr_pages; int /*<<< orphan*/ * sglist; } ;
struct videobuf_buffer {size_t bsize; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int,unsigned int) ; 
 unsigned int get_order (size_t) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_free_mmap_buffer (struct videobuf_buffer*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 struct videobuf_dmabuf* videobuf_to_dma (struct videobuf_buffer*) ; 

__attribute__((used)) static int omap24xxcam_vbq_alloc_mmap_buffer(struct videobuf_buffer *vb)
{
	unsigned int order;
	size_t alloc_size, size = vb->bsize; /* vb->bsize is page aligned */
	struct page *page;
	int max_pages, err = 0, i = 0;
	struct videobuf_dmabuf *dma = videobuf_to_dma(vb);

	/*
	 * allocate maximum size scatter-gather list. Note this is
	 * overhead. We may not use as many entries as we allocate
	 */
	max_pages = vb->bsize >> PAGE_SHIFT;
	dma->sglist = kcalloc(max_pages, sizeof(*dma->sglist), GFP_KERNEL);
	if (dma->sglist == NULL) {
		err = -ENOMEM;
		goto out;
	}

	while (size) {
		order = get_order(size);
		/*
		 * do not over-allocate even if we would get larger
		 * contiguous chunk that way
		 */
		if ((PAGE_SIZE << order) > size)
			order--;

		/* try to allocate as many contiguous pages as possible */
		page = alloc_pages(GFP_KERNEL | GFP_DMA, order);
		/* if allocation fails, try to allocate smaller amount */
		while (page == NULL) {
			order--;
			page = alloc_pages(GFP_KERNEL | GFP_DMA, order);
			if (page == NULL && !order) {
				err = -ENOMEM;
				goto out;
			}
		}
		size -= (PAGE_SIZE << order);

		/* append allocated chunk of pages into scatter-gather list */
		sg_set_page(&dma->sglist[i], page, PAGE_SIZE << order, 0);
		dma->sglen++;
		i++;

		alloc_size = (PAGE_SIZE << order);

		/* clear pages before giving them to user space */
		memset(page_address(page), 0, alloc_size);

		/* mark allocated pages reserved */
		do {
			SetPageReserved(page++);
		} while (alloc_size -= PAGE_SIZE);
	}
	/*
	 * REVISIT: not fully correct to assign nr_pages == sglen but
	 * video-buf is passing nr_pages for e.g. unmap_sg calls
	 */
	dma->nr_pages = dma->sglen;
	dma->direction = PCI_DMA_FROMDEVICE;

	return 0;

out:
	omap24xxcam_vbq_free_mmap_buffer(vb);
	return err;
}