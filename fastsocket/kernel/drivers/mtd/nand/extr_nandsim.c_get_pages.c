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
struct nandsim {scalar_t__ held_cnt; struct page** held_pages; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ pgoff_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ NS_MAX_HELD_PAGES ; 
 size_t PAGE_CACHE_SHIFT ; 
 struct page* find_get_page (struct address_space*,scalar_t__) ; 
 struct page* find_or_create_page (struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pages (struct nandsim*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  write_inode_now (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_pages(struct nandsim *ns, struct file *file, size_t count, loff_t pos)
{
	pgoff_t index, start_index, end_index;
	struct page *page;
	struct address_space *mapping = file->f_mapping;

	start_index = pos >> PAGE_CACHE_SHIFT;
	end_index = (pos + count - 1) >> PAGE_CACHE_SHIFT;
	if (end_index - start_index + 1 > NS_MAX_HELD_PAGES)
		return -EINVAL;
	ns->held_cnt = 0;
	for (index = start_index; index <= end_index; index++) {
		page = find_get_page(mapping, index);
		if (page == NULL) {
			page = find_or_create_page(mapping, index, GFP_NOFS);
			if (page == NULL) {
				write_inode_now(mapping->host, 1);
				page = find_or_create_page(mapping, index, GFP_NOFS);
			}
			if (page == NULL) {
				put_pages(ns);
				return -ENOMEM;
			}
			unlock_page(page);
		}
		ns->held_pages[ns->held_cnt++] = page;
	}
	return 0;
}