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

/* Variables and functions */
 int /*<<< orphan*/  NR_ACTIVE_ANON ; 
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int global_page_state (int /*<<< orphan*/ ) ; 
 scalar_t__ nr_swap_pages ; 

unsigned long global_reclaimable_pages(void)
{
	int nr;

	nr = global_page_state(NR_ACTIVE_FILE) +
	     global_page_state(NR_INACTIVE_FILE);

	if (nr_swap_pages > 0)
		nr += global_page_state(NR_ACTIVE_ANON) +
		      global_page_state(NR_INACTIVE_ANON);

	return nr;
}