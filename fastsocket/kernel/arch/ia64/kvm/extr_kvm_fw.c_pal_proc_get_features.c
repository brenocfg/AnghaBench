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
struct ia64_pal_retval {int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; int /*<<< orphan*/  status; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_pal_proc_get_features (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  kvm_get_pal_call_data (struct kvm_vcpu*,long*,long*,long*,long*) ; 

__attribute__((used)) static struct ia64_pal_retval pal_proc_get_features(struct kvm_vcpu *vcpu)
{

	struct ia64_pal_retval result = {0, 0, 0, 0};
	long in0, in1, in2, in3;

	kvm_get_pal_call_data(vcpu, &in0, &in1, &in2, &in3);
	result.status = ia64_pal_proc_get_features(&result.v0, &result.v1,
			&result.v2, in2);

	return result;
}