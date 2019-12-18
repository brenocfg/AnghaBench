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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/ * EXT3_JOURNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_invalidatepage (int /*<<< orphan*/ *,struct page*,unsigned long) ; 
 int /*<<< orphan*/  trace_ext3_invalidatepage (struct page*,unsigned long) ; 

__attribute__((used)) static void ext3_invalidatepage(struct page *page, unsigned long offset)
{
	journal_t *journal = EXT3_JOURNAL(page->mapping->host);

	trace_ext3_invalidatepage(page, offset);

	/*
	 * If it's a full truncate we just forget about the pending dirtying
	 */
	if (offset == 0)
		ClearPageChecked(page);

	journal_invalidatepage(journal, page, offset);
}