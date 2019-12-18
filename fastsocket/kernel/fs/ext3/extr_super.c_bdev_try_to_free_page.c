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
struct super_block {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __GFP_WAIT ; 
 int journal_try_to_free_buffers (int /*<<< orphan*/ *,struct page*,int) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int bdev_try_to_free_page(struct super_block *sb, struct page *page,
				 gfp_t wait)
{
	journal_t *journal = EXT3_SB(sb)->s_journal;

	WARN_ON(PageChecked(page));
	if (!page_has_buffers(page))
		return 0;
	if (journal)
		return journal_try_to_free_buffers(journal, page, 
						   wait & ~__GFP_WAIT);
	return try_to_free_buffers(page);
}