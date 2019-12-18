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
struct page {int dummy; } ;
struct nfs_page_array {unsigned int npages; int /*<<< orphan*/ * pagevec; int /*<<< orphan*/ * page_array; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

bool nfs_pgarray_set(struct nfs_page_array *p, unsigned int pagecount)
{
	p->npages = pagecount;
	if (pagecount <= ARRAY_SIZE(p->page_array))
		p->pagevec = p->page_array;
	else {
		p->pagevec = kcalloc(pagecount, sizeof(struct page *), GFP_KERNEL);
		if (!p->pagevec)
			p->npages = 0;
	}
	return p->pagevec != NULL;
}