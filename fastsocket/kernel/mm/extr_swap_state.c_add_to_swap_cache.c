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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __add_to_swap_cache (struct page*,int /*<<< orphan*/ ) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 

int add_to_swap_cache(struct page *page, swp_entry_t entry, gfp_t gfp_mask)
{
	int error;

	error = radix_tree_preload(gfp_mask);
	if (!error) {
		error = __add_to_swap_cache(page, entry);
		radix_tree_preload_end();
	}
	return error;
}