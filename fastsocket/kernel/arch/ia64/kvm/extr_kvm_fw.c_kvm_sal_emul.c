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
typedef  int /*<<< orphan*/  u64 ;
struct sal_ret_values {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_get_sal_call_data (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sal_ret_values sal_emulator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sal_result (struct kvm_vcpu*,struct sal_ret_values) ; 

void kvm_sal_emul(struct kvm_vcpu *vcpu)
{

	struct sal_ret_values result;
	u64 index, in1, in2, in3, in4, in5, in6, in7;

	kvm_get_sal_call_data(vcpu, &index, &in1, &in2,
			&in3, &in4, &in5, &in6, &in7);
	result = sal_emulator(vcpu->kvm, index, in1, in2, in3,
					in4, in5, in6, in7);
	set_sal_result(vcpu, result);
}