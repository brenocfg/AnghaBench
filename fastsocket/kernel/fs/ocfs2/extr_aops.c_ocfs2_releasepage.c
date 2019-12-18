#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_3__* mapping; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {TYPE_1__* journal; } ;
struct TYPE_7__ {TYPE_2__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * j_journal; } ;

/* Variables and functions */
 TYPE_4__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int jbd2_journal_try_to_free_buffers (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 

__attribute__((used)) static int ocfs2_releasepage(struct page *page, gfp_t wait)
{
	journal_t *journal = OCFS2_SB(page->mapping->host->i_sb)->journal->j_journal;

	if (!page_has_buffers(page))
		return 0;
	return jbd2_journal_try_to_free_buffers(journal, page, wait);
}