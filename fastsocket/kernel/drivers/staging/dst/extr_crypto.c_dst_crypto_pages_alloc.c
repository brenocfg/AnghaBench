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
struct dst_crypto_engine {int page_num; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_crypto_pages_alloc(struct dst_crypto_engine *e, int num)
{
	int i;

	e->pages = kmalloc(num * sizeof(struct page **), GFP_KERNEL);
	if (!e->pages)
		return -ENOMEM;

	for (i=0; i<num; ++i) {
		e->pages[i] = alloc_page(GFP_KERNEL);
		if (!e->pages[i])
			goto err_out_free_pages;
	}

	e->page_num = num;
	return 0;

err_out_free_pages:
	while (--i >= 0)
		__free_page(e->pages[i]);

	kfree(e->pages);
	return -ENOMEM;
}