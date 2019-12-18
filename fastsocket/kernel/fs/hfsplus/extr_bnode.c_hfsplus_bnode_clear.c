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
 int PAGE_CACHE_MASK ; 
 int PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void hfs_bnode_clear(struct hfs_bnode *node, int off, int len)
{
	struct page **pagep;
	int l;

	off += node->page_offset;
	pagep = node->page + (off >> PAGE_CACHE_SHIFT);
	off &= ~PAGE_CACHE_MASK;

	l = min(len, (int)PAGE_CACHE_SIZE - off);
	memset(kmap(*pagep) + off, 0, l);
	set_page_dirty(*pagep);
	kunmap(*pagep);

	while ((len -= l) != 0) {
		l = min(len, (int)PAGE_CACHE_SIZE);
		memset(kmap(*++pagep), 0, l);
		set_page_dirty(*pagep);
		kunmap(*pagep);
	}
}