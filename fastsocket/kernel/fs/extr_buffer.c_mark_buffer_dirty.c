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
struct buffer_head {struct page* b_page; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __set_page_dirty (struct page*,struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_set_buffer_dirty (struct buffer_head*) ; 

void mark_buffer_dirty(struct buffer_head *bh)
{
	WARN_ON_ONCE(!buffer_uptodate(bh));

	/*
	 * Very *carefully* optimize the it-is-already-dirty case.
	 *
	 * Don't let the final "is it dirty" escape to before we
	 * perhaps modified the buffer.
	 */
	if (buffer_dirty(bh)) {
		smp_mb();
		if (buffer_dirty(bh))
			return;
	}

	if (!test_set_buffer_dirty(bh)) {
		struct page *page = bh->b_page;
		if (!TestSetPageDirty(page)) {
			struct address_space *mapping = page_mapping(page);
			if (mapping)
				__set_page_dirty(page, mapping, 0);
		}
	}
}