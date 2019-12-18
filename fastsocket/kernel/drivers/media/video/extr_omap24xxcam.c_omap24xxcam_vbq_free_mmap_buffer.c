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
struct videobuf_dmabuf {int sglen; int /*<<< orphan*/ * sglist; } ;
struct videobuf_buffer {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 size_t sg_dma_len (int /*<<< orphan*/ *) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 
 struct videobuf_dmabuf* videobuf_to_dma (struct videobuf_buffer*) ; 

__attribute__((used)) static void omap24xxcam_vbq_free_mmap_buffer(struct videobuf_buffer *vb)
{
	struct videobuf_dmabuf *dma = videobuf_to_dma(vb);
	size_t alloc_size;
	struct page *page;
	int i;

	if (dma->sglist == NULL)
		return;

	i = dma->sglen;
	while (i) {
		i--;
		alloc_size = sg_dma_len(&dma->sglist[i]);
		page = sg_page(&dma->sglist[i]);
		do {
			ClearPageReserved(page++);
		} while (alloc_size -= PAGE_SIZE);
		__free_pages(sg_page(&dma->sglist[i]),
			     get_order(sg_dma_len(&dma->sglist[i])));
	}

	kfree(dma->sglist);
	dma->sglist = NULL;
}