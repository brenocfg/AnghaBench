#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ ret; } ;
struct TYPE_7__ {TYPE_2__ pal_data; } ;
struct exit_ctl_data {scalar_t__ exit_reason; TYPE_3__ u; } ;
struct TYPE_8__ {struct exit_ctl_data exit_data; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_PAL_CALL ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/  vcpu_set_gr (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_pal_call_result(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p = &vcpu->arch.exit_data;

	if (p->exit_reason == EXIT_REASON_PAL_CALL) {
		vcpu_set_gr(vcpu, 8, p->u.pal_data.ret.status, 0);
		vcpu_set_gr(vcpu, 9, p->u.pal_data.ret.v0, 0);
		vcpu_set_gr(vcpu, 10, p->u.pal_data.ret.v1, 0);
		vcpu_set_gr(vcpu, 11, p->u.pal_data.ret.v2, 0);
	} else
		panic_vm(vcpu, "Mis-set for exit reason!\n");
}