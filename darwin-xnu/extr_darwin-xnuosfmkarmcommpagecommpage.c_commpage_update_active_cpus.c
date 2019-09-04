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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_ACTIVE_CPUS ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 int /*<<< orphan*/  commPagePtr ; 
 int /*<<< orphan*/  processor_avail_count ; 

void
commpage_update_active_cpus(void)
{
        if (!commPagePtr)
                return;
	*((uint8_t *)(_COMM_PAGE_ACTIVE_CPUS+_COMM_PAGE_RW_OFFSET)) = processor_avail_count;
}