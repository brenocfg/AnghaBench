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
union hv_synic_sint {int masked; int /*<<< orphan*/  as_uint64; } ;
union hv_synic_simp {int /*<<< orphan*/  as_uint64; scalar_t__ base_simp_gpa; scalar_t__ simp_enabled; } ;
union hv_synic_siefp {int /*<<< orphan*/  as_uint64; scalar_t__ base_siefp_gpa; scalar_t__ siefp_enabled; } ;
struct TYPE_2__ {scalar_t__* synic_event_page; scalar_t__* synic_message_page; int /*<<< orphan*/  synic_initialized; } ;

/* Variables and functions */
 scalar_t__ HV_X64_MSR_SIEFP ; 
 scalar_t__ HV_X64_MSR_SIMP ; 
 scalar_t__ HV_X64_MSR_SINT0 ; 
 scalar_t__ VMBUS_MESSAGE_SINT ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 TYPE_1__ hv_context ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  wrmsrl (scalar_t__,int /*<<< orphan*/ ) ; 

void hv_synic_cleanup(void *arg)
{
	union hv_synic_sint shared_sint;
	union hv_synic_simp simp;
	union hv_synic_siefp siefp;
	int cpu = smp_processor_id();

	if (!hv_context.synic_initialized)
		return;

	rdmsrl(HV_X64_MSR_SINT0 + VMBUS_MESSAGE_SINT, shared_sint.as_uint64);

	shared_sint.masked = 1;

	/* Need to correctly cleanup in the case of SMP!!! */
	/* Disable the interrupt */
	wrmsrl(HV_X64_MSR_SINT0 + VMBUS_MESSAGE_SINT, shared_sint.as_uint64);

	rdmsrl(HV_X64_MSR_SIMP, simp.as_uint64);
	simp.simp_enabled = 0;
	simp.base_simp_gpa = 0;

	wrmsrl(HV_X64_MSR_SIMP, simp.as_uint64);

	rdmsrl(HV_X64_MSR_SIEFP, siefp.as_uint64);
	siefp.siefp_enabled = 0;
	siefp.base_siefp_gpa = 0;

	wrmsrl(HV_X64_MSR_SIEFP, siefp.as_uint64);

	free_page((unsigned long)hv_context.synic_message_page[cpu]);
	free_page((unsigned long)hv_context.synic_event_page[cpu]);
}