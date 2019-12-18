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
struct pohmelfs_sb {int trans_max_pages; } ;
struct pohmelfs_crypto_engine {unsigned int page_num; int /*<<< orphan*/ * pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_crypto_pages_alloc(struct pohmelfs_crypto_engine *e, struct pohmelfs_sb *psb)
{
	unsigned int i;

	e->pages = kmalloc(psb->trans_max_pages * sizeof(struct page *), GFP_KERNEL);
	if (!e->pages)
		return -ENOMEM;

	for (i=0; i<psb->trans_max_pages; ++i) {
		e->pages[i] = alloc_page(GFP_KERNEL);
		if (!e->pages[i])
			break;
	}

	e->page_num = i;
	if (!e->page_num)
		goto err_out_free;

	return 0;

err_out_free:
	kfree(e->pages);
	return -ENOMEM;
}