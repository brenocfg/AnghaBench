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
struct page {TYPE_1__* mapping; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int E2BIG ; 
 int ENOMEM ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int hostfs_do_readlink (char*,char*,int) ; 
 char* inode_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int hostfs_link_readpage(struct file *file, struct page *page)
{
	char *buffer, *name;
	int err;

	buffer = kmap(page);
	name = inode_name(page->mapping->host, 0);
	if (name == NULL)
		return -ENOMEM;
	err = hostfs_do_readlink(name, buffer, PAGE_CACHE_SIZE);
	kfree(name);
	if (err == PAGE_CACHE_SIZE)
		err = -E2BIG;
	else if (err > 0) {
		flush_dcache_page(page);
		SetPageUptodate(page);
		if (PageError(page)) ClearPageError(page);
		err = 0;
	}
	kunmap(page);
	unlock_page(page);
	return err;
}