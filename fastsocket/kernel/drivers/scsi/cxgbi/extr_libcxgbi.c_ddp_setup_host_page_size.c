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
 scalar_t__ DDP_PGIDX_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ddp_adjust_page_table () ; 
 scalar_t__ ddp_find_page_index (int /*<<< orphan*/ ) ; 
 scalar_t__ page_idx ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void ddp_setup_host_page_size(void)
{
	if (page_idx == DDP_PGIDX_MAX) {
		page_idx = ddp_find_page_index(PAGE_SIZE);

		if (page_idx == DDP_PGIDX_MAX) {
			pr_info("system PAGE %lu, update hw.\n", PAGE_SIZE);
			if (ddp_adjust_page_table() < 0) {
				pr_info("PAGE %lu, disable ddp.\n", PAGE_SIZE);
				return;
			}
			page_idx = ddp_find_page_index(PAGE_SIZE);
		}
		pr_info("system PAGE %lu, ddp idx %u.\n", PAGE_SIZE, page_idx);
	}
}