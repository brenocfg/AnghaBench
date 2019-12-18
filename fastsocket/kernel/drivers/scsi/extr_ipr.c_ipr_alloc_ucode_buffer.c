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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct ipr_sglist {int order; int num_sg; struct scatterlist* scatterlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPR_MAX_SGLIST ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  ipr_trace ; 
 int /*<<< orphan*/  kfree (struct ipr_sglist*) ; 
 struct ipr_sglist* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ipr_sglist *ipr_alloc_ucode_buffer(int buf_len)
{
	int sg_size, order, bsize_elem, num_elem, i, j;
	struct ipr_sglist *sglist;
	struct scatterlist *scatterlist;
	struct page *page;

	/* Get the minimum size per scatter/gather element */
	sg_size = buf_len / (IPR_MAX_SGLIST - 1);

	/* Get the actual size per element */
	order = get_order(sg_size);

	/* Determine the actual number of bytes per element */
	bsize_elem = PAGE_SIZE * (1 << order);

	/* Determine the actual number of sg entries needed */
	if (buf_len % bsize_elem)
		num_elem = (buf_len / bsize_elem) + 1;
	else
		num_elem = buf_len / bsize_elem;

	/* Allocate a scatter/gather list for the DMA */
	sglist = kzalloc(sizeof(struct ipr_sglist) +
			 (sizeof(struct scatterlist) * (num_elem - 1)),
			 GFP_KERNEL);

	if (sglist == NULL) {
		ipr_trace;
		return NULL;
	}

	scatterlist = sglist->scatterlist;
	sg_init_table(scatterlist, num_elem);

	sglist->order = order;
	sglist->num_sg = num_elem;

	/* Allocate a bunch of sg elements */
	for (i = 0; i < num_elem; i++) {
		page = alloc_pages(GFP_KERNEL, order);
		if (!page) {
			ipr_trace;

			/* Free up what we already allocated */
			for (j = i - 1; j >= 0; j--)
				__free_pages(sg_page(&scatterlist[j]), order);
			kfree(sglist);
			return NULL;
		}

		sg_set_page(&scatterlist[i], page, 0, 0);
	}

	return sglist;
}