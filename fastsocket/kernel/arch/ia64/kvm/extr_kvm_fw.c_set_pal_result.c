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
struct kvm_vcpu {int dummy; } ;
struct ia64_pal_retval {int dummy; } ;
struct TYPE_3__ {struct ia64_pal_retval ret; } ;
struct TYPE_4__ {TYPE_1__ pal_data; } ;
struct exit_ctl_data {scalar_t__ exit_reason; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_PAL_CALL ; 
 int /*<<< orphan*/  INIT_PAL_STATUS_UNIMPLEMENTED (struct ia64_pal_retval) ; 
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 

__attribute__((used)) static void set_pal_result(struct kvm_vcpu *vcpu,
		struct ia64_pal_retval result) {

	struct exit_ctl_data *p;

	p = kvm_get_exit_data(vcpu);
	if (p && p->exit_reason == EXIT_REASON_PAL_CALL) {
		p->u.pal_data.ret = result;
		return ;
	}
	INIT_PAL_STATUS_UNIMPLEMENTED(p->u.pal_data.ret);
}