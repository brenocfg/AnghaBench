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
struct hfs_btree {int dummy; } ;
struct hfs_bnode {struct page** page; scalar_t__ page_offset; struct hfs_btree* tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BNODE_MOD ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void hfs_bnode_copy(struct hfs_bnode *dst_node, int dst,
		struct hfs_bnode *src_node, int src, int len)
{
	struct hfs_btree *tree;
	struct page *src_page, *dst_page;

	dprint(DBG_BNODE_MOD, "copybytes: %u,%u,%u\n", dst, src, len);
	if (!len)
		return;
	tree = src_node->tree;
	src += src_node->page_offset;
	dst += dst_node->page_offset;
	src_page = src_node->page[0];
	dst_page = dst_node->page[0];

	memcpy(kmap(dst_page) + dst, kmap(src_page) + src, len);
	kunmap(src_page);
	kunmap(dst_page);
	set_page_dirty(dst_page);
}