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
struct page {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_locked ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  wake_up_page (struct page*,int /*<<< orphan*/ ) ; 

void unlock_page(struct page *page)
{
	VM_BUG_ON(!PageLocked(page));
	clear_bit_unlock(PG_locked, &page->flags);
	smp_mb__after_clear_bit();
	wake_up_page(page, PG_locked);
}