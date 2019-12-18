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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_HAS_CACHE ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_swapcache (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned char swap_entry_free (struct swap_info_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct swap_info_struct* swap_info_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_lock ; 

void swapcache_free(swp_entry_t entry, struct page *page)
{
	struct swap_info_struct *p;
	unsigned char count;

	p = swap_info_get(entry);
	if (p) {
		count = swap_entry_free(p, entry, SWAP_HAS_CACHE);
		if (page)
			mem_cgroup_uncharge_swapcache(page, entry, count != 0);
		spin_unlock(&swap_lock);
	}
}