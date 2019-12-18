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
struct hfs_bnode {struct page** page; scalar_t__ page_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BNODE_MOD ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*,int,int,int) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void hfs_bnode_move(struct hfs_bnode *node, int dst, int src, int len)
{
	struct page *page;
	void *ptr;

	dprint(DBG_BNODE_MOD, "movebytes: %u,%u,%u\n", dst, src, len);
	if (!len)
		return;
	src += node->page_offset;
	dst += node->page_offset;
	page = node->page[0];
	ptr = kmap(page);
	memmove(ptr + dst, ptr + src, len);
	kunmap(page);
	set_page_dirty(page);
}