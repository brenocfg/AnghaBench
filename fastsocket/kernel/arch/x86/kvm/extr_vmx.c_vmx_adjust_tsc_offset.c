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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  TSC_OFFSET ; 
 int /*<<< orphan*/  trace_kvm_write_tsc_offset (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ vmcs_read64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vmx_adjust_tsc_offset(struct kvm_vcpu *vcpu, s64 adjustment, bool host)
{
	u64 offset = vmcs_read64(TSC_OFFSET);
	vmcs_write64(TSC_OFFSET, offset + adjustment);

	trace_kvm_write_tsc_offset(vcpu->vcpu_id, offset,
				   offset + adjustment);
}