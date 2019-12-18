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
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 unsigned long min (unsigned long,int) ; 
 int node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numa_node_id () ; 

unsigned long max_sane_readahead(unsigned long nr)
{
	return min(nr, (node_page_state(numa_node_id(), NR_INACTIVE_FILE)
		+ node_page_state(numa_node_id(), NR_FREE_PAGES)) / 2);
}