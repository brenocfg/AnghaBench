#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int /*<<< orphan*/  filler_t ;
struct TYPE_2__ {scalar_t__ readpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  nilfs_check_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_put_page (struct page*) ; 
 struct page* read_cache_page (struct address_space*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

__attribute__((used)) static struct page *nilfs_get_page(struct inode *dir, unsigned long n)
{
	struct address_space *mapping = dir->i_mapping;
	struct page *page = read_cache_page(mapping, n,
				(filler_t *)mapping->a_ops->readpage, NULL);
	if (!IS_ERR(page)) {
		wait_on_page_locked(page);
		kmap(page);
		if (!PageUptodate(page))
			goto fail;
		if (!PageChecked(page))
			nilfs_check_page(page);
		if (PageError(page))
			goto fail;
	}
	return page;

fail:
	nilfs_put_page(page);
	return ERR_PTR(-EIO);
}