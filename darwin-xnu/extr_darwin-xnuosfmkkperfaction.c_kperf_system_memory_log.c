#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vm_pageout_compressions; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  PERF_MI_SYS_DATA ; 
 int /*<<< orphan*/  PERF_MI_SYS_DATA_2 ; 
 scalar_t__ VM_PAGE_COMPRESSOR_COUNT ; 
 scalar_t__ vm_page_active_count ; 
 scalar_t__ vm_page_anonymous_count ; 
 scalar_t__ vm_page_external_count ; 
 scalar_t__ vm_page_free_count ; 
 scalar_t__ vm_page_inactive_count ; 
 scalar_t__ vm_page_internal_count ; 
 scalar_t__ vm_page_speculative_count ; 
 scalar_t__ vm_page_wire_count ; 
 TYPE_1__ vm_pageout_vminfo ; 

__attribute__((used)) static void
kperf_system_memory_log(void)
{
	BUF_DATA(PERF_MI_SYS_DATA, (uintptr_t)vm_page_free_count,
			(uintptr_t)vm_page_wire_count, (uintptr_t)vm_page_external_count,
			(uintptr_t)(vm_page_active_count + vm_page_inactive_count +
			vm_page_speculative_count));
	BUF_DATA(PERF_MI_SYS_DATA_2, (uintptr_t)vm_page_anonymous_count,
			(uintptr_t)vm_page_internal_count,
			(uintptr_t)vm_pageout_vminfo.vm_pageout_compressions,
			(uintptr_t)VM_PAGE_COMPRESSOR_COUNT);
}