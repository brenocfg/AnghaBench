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
struct pmcraid_sglist {int order; int num_sg; struct scatterlist* scatterlist; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int PMCRAID_MAX_IOADLS ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages (int,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  kfree (struct pmcraid_sglist*) ; 
 struct pmcraid_sglist* kzalloc (int,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pmcraid_sglist *pmcraid_alloc_sglist(int buflen)
{
	struct pmcraid_sglist *sglist;
	struct scatterlist *scatterlist;
	struct page *page;
	int num_elem, i, j;
	int sg_size;
	int order;
	int bsize_elem;

	sg_size = buflen / (PMCRAID_MAX_IOADLS - 1);
	order = (sg_size > 0) ? get_order(sg_size) : 0;
	bsize_elem = PAGE_SIZE * (1 << order);

	/* Determine the actual number of sg entries needed */
	if (buflen % bsize_elem)
		num_elem = (buflen / bsize_elem) + 1;
	else
		num_elem = buflen / bsize_elem;

	/* Allocate a scatter/gather list for the DMA */
	sglist = kzalloc(sizeof(struct pmcraid_sglist) +
			 (sizeof(struct scatterlist) * (num_elem - 1)),
			 GFP_KERNEL);

	if (sglist == NULL)
		return NULL;

	scatterlist = sglist->scatterlist;
	sg_init_table(scatterlist, num_elem);
	sglist->order = order;
	sglist->num_sg = num_elem;
	sg_size = buflen;

	for (i = 0; i < num_elem; i++) {
		page = alloc_pages(GFP_KERNEL|GFP_DMA|__GFP_ZERO, order);
		if (!page) {
			for (j = i - 1; j >= 0; j--)
				__free_pages(sg_page(&scatterlist[j]), order);
			kfree(sglist);
			return NULL;
		}

		sg_set_page(&scatterlist[i], page,
			sg_size < bsize_elem ? sg_size : bsize_elem, 0);
		sg_size -= bsize_elem;
	}

	return sglist;
}