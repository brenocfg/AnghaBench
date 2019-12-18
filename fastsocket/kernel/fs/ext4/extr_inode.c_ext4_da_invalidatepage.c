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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  ext4_da_page_release_reservation (struct page*,unsigned long) ; 
 int /*<<< orphan*/  ext4_invalidatepage (struct page*,unsigned long) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 

__attribute__((used)) static void ext4_da_invalidatepage(struct page *page, unsigned long offset)
{
	/*
	 * Drop reserved blocks
	 */
	BUG_ON(!PageLocked(page));
	if (!page_has_buffers(page))
		goto out;

	ext4_da_page_release_reservation(page, offset);

out:
	ext4_invalidatepage(page, offset);

	return;
}