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
union hv_x64_msr_hypercall_contents {int enable; scalar_t__ as_uint64; int /*<<< orphan*/  guest_physical_address; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {void* hypercall_page; scalar_t__ guestid; int /*<<< orphan*/  event_dpc; int /*<<< orphan*/  vp_index; int /*<<< orphan*/  synic_message_page; int /*<<< orphan*/  synic_event_page; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HV_X64_MSR_GUEST_OS_ID ; 
 int /*<<< orphan*/  HV_X64_MSR_HYPERCALL ; 
 int /*<<< orphan*/  LINUX_VERSION_CODE ; 
 int NR_CPUS ; 
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* __vmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ generate_guest_id (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ hv_context ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int query_hypervisor_info () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int /*<<< orphan*/  vmalloc_to_pfn (void*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

int hv_init(void)
{
	int max_leaf;
	union hv_x64_msr_hypercall_contents hypercall_msr;
	void *virtaddr = NULL;
	__u8 d1 = 0x20; /* REDHAT */
	__u16 d2 = 0;

	memset(hv_context.synic_event_page, 0, sizeof(void *) * NR_CPUS);
	memset(hv_context.synic_message_page, 0,
	       sizeof(void *) * NR_CPUS);
	memset(hv_context.vp_index, 0,
	       sizeof(int) * NR_CPUS);
	memset(hv_context.event_dpc, 0,
	       sizeof(void *) * NR_CPUS);

	max_leaf = query_hypervisor_info();

	/*
	 * Write our OS ID.
	 */
	hv_context.guestid = generate_guest_id(d1, LINUX_VERSION_CODE, d2);
	wrmsrl(HV_X64_MSR_GUEST_OS_ID, hv_context.guestid);

	/* See if the hypercall page is already set */
	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uint64);

	virtaddr = __vmalloc(PAGE_SIZE, GFP_KERNEL, PAGE_KERNEL_EXEC);

	if (!virtaddr)
		goto cleanup;

	hypercall_msr.enable = 1;

	hypercall_msr.guest_physical_address = vmalloc_to_pfn(virtaddr);
	wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uint64);

	/* Confirm that hypercall page did get setup. */
	hypercall_msr.as_uint64 = 0;
	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uint64);

	if (!hypercall_msr.enable)
		goto cleanup;

	hv_context.hypercall_page = virtaddr;

	return 0;

cleanup:
	if (virtaddr) {
		if (hypercall_msr.enable) {
			hypercall_msr.as_uint64 = 0;
			wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uint64);
		}

		vfree(virtaddr);
	}

	return -ENOTSUPP;
}