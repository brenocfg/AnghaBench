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
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EXT3_JOURNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int journal_try_to_free_buffers (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  trace_ext3_releasepage (struct page*) ; 

__attribute__((used)) static int ext3_releasepage(struct page *page, gfp_t wait)
{
	journal_t *journal = EXT3_JOURNAL(page->mapping->host);

	trace_ext3_releasepage(page);
	WARN_ON(PageChecked(page));
	if (!page_has_buffers(page))
		return 0;
	return journal_try_to_free_buffers(journal, page, wait);
}