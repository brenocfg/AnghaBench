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
struct kvm_vcpu {int dummy; } ;
struct ia64_pal_retval {int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  pal_tc_info_u_t ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_pal_vm_info (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_get_pal_call_data (struct kvm_vcpu*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static struct ia64_pal_retval pal_vm_info(struct kvm_vcpu *vcpu)
{
	struct ia64_pal_retval result;
	unsigned long in0, in1, in2, in3;

	kvm_get_pal_call_data(vcpu, &in0, &in1, &in2, &in3);

	result.status = ia64_pal_vm_info(in1, in2,
			(pal_tc_info_u_t *)&result.v1, &result.v2);

	return result;
}