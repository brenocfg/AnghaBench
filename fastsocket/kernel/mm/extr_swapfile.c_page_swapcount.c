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
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {int /*<<< orphan*/ * swap_map; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int swap_count (int /*<<< orphan*/ ) ; 
 struct swap_info_struct* swap_info_get (TYPE_1__) ; 
 int /*<<< orphan*/  swap_lock ; 
 size_t swp_offset (TYPE_1__) ; 

__attribute__((used)) static inline int page_swapcount(struct page *page)
{
	int count = 0;
	struct swap_info_struct *p;
	swp_entry_t entry;

	entry.val = page_private(page);
	p = swap_info_get(entry);
	if (p) {
		count = swap_count(p->swap_map[swp_offset(entry)]);
		spin_unlock(&swap_lock);
	}
	return count;
}