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
struct zone {int /*<<< orphan*/  lru_lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_UNEVICTABLE ; 
 int /*<<< orphan*/  SetPageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageUnevictable (struct page*) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct zone*,struct page*,int /*<<< orphan*/ ) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void add_page_to_unevictable_list(struct page *page)
{
	struct zone *zone = page_zone(page);

	spin_lock_irq(&zone->lru_lock);
	SetPageUnevictable(page);
	SetPageLRU(page);
	add_page_to_lru_list(zone, page, LRU_UNEVICTABLE);
	spin_unlock_irq(&zone->lru_lock);
}