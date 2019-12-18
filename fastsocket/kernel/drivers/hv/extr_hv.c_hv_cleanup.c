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
union hv_x64_msr_hypercall_contents {scalar_t__ as_uint64; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hypercall_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_GUEST_OS_ID ; 
 int /*<<< orphan*/  HV_X64_MSR_HYPERCALL ; 
 TYPE_1__ hv_context ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

void hv_cleanup(void)
{
	union hv_x64_msr_hypercall_contents hypercall_msr;

	/* Reset our OS id */
	wrmsrl(HV_X64_MSR_GUEST_OS_ID, 0);

	if (hv_context.hypercall_page) {
		hypercall_msr.as_uint64 = 0;
		wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uint64);
		vfree(hv_context.hypercall_page);
		hv_context.hypercall_page = NULL;
	}
}