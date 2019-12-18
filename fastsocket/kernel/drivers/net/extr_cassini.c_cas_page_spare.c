#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cas {int /*<<< orphan*/  rx_inuse_lock; int /*<<< orphan*/  rx_inuse_list; TYPE_1__*** rx_pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ cas_page_t ;

/* Variables and functions */
 TYPE_1__* cas_page_dequeue (struct cas*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline cas_page_t *cas_page_spare(struct cas *cp, const int index)
{
	cas_page_t *page = cp->rx_pages[1][index];
	cas_page_t *new;

	if (page_count(page->buffer) == 1)
		return page;

	new = cas_page_dequeue(cp);
	if (new) {
		spin_lock(&cp->rx_inuse_lock);
		list_add(&page->list, &cp->rx_inuse_list);
		spin_unlock(&cp->rx_inuse_lock);
	}
	return new;
}