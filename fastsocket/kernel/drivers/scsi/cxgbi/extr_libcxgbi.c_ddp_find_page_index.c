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
 int DDP_PGIDX_MAX ; 
 unsigned long* ddp_page_shift ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 

__attribute__((used)) static int ddp_find_page_index(unsigned long pgsz)
{
	int i;

	for (i = 0; i < DDP_PGIDX_MAX; i++) {
		if (pgsz == (1UL << ddp_page_shift[i]))
			return i;
	}
	pr_info("ddp page size %lu not supported.\n", pgsz);
	return DDP_PGIDX_MAX;
}