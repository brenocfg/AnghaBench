#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  in7; int /*<<< orphan*/  in6; int /*<<< orphan*/  in5; int /*<<< orphan*/  in4; int /*<<< orphan*/  in3; int /*<<< orphan*/  in2; int /*<<< orphan*/  in1; int /*<<< orphan*/  in0; } ;
struct TYPE_4__ {TYPE_1__ sal_data; } ;
struct exit_ctl_data {scalar_t__ exit_reason; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_SAL_CALL ; 
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_get_sal_call_data(struct kvm_vcpu *vcpu, u64 *in0, u64 *in1,
		u64 *in2, u64 *in3, u64 *in4, u64 *in5, u64 *in6, u64 *in7){

	struct exit_ctl_data *p;

	p = kvm_get_exit_data(vcpu);

	if (p) {
		if (p->exit_reason == EXIT_REASON_SAL_CALL) {
			*in0 = p->u.sal_data.in0;
			*in1 = p->u.sal_data.in1;
			*in2 = p->u.sal_data.in2;
			*in3 = p->u.sal_data.in3;
			*in4 = p->u.sal_data.in4;
			*in5 = p->u.sal_data.in5;
			*in6 = p->u.sal_data.in6;
			*in7 = p->u.sal_data.in7;
			return ;
		}
	}
	*in0 = 0;
}