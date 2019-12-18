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
typedef  int u64 ;

/* Variables and functions */
 scalar_t__ KVM_P2M_BASE ; 
 int KVM_P2M_SIZE ; 
 int /*<<< orphan*/  current_vcpu ; 
 int /*<<< orphan*/  panic_vm (int /*<<< orphan*/ ,char*,int) ; 

u64 kvm_get_mpt_entry(u64 gpfn)
{
	u64 *base = (u64 *) KVM_P2M_BASE;

	if (gpfn >= (KVM_P2M_SIZE >> 3))
		panic_vm(current_vcpu, "Invalid gpfn =%lx\n", gpfn);

	return *(base + gpfn);
}