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
struct dentry {TYPE_1__* d_inode; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_size; struct address_space* i_mapping; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PAGE_SIZE ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  nd_terminate_link (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct page* read_mapping_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *page_getlink(struct dentry * dentry, struct page **ppage)
{
	char *kaddr;
	struct page *page;
	struct address_space *mapping = dentry->d_inode->i_mapping;
	page = read_mapping_page(mapping, 0, NULL);
	if (IS_ERR(page))
		return (char*)page;
	*ppage = page;
	kaddr = kmap(page);
	nd_terminate_link(kaddr, dentry->d_inode->i_size, PAGE_SIZE - 1);
	return kaddr;
}