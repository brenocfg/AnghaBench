#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tree_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __delete_from_swap_cache (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapcache_free (TYPE_1__,struct page*) ; 
 TYPE_2__ swapper_space ; 

void delete_from_swap_cache(struct page *page)
{
	swp_entry_t entry;

	entry.val = page_private(page);

	spin_lock_irq(&swapper_space.tree_lock);
	__delete_from_swap_cache(page);
	spin_unlock_irq(&swapper_space.tree_lock);

	swapcache_free(entry, page);
	page_cache_release(page);
}