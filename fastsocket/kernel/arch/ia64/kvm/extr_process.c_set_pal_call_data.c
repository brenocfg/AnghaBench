#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long gr29; unsigned long gr28; void* gr31; void* gr30; } ;
struct TYPE_6__ {TYPE_2__ pal_data; } ;
struct exit_ctl_data {int /*<<< orphan*/  exit_reason; TYPE_3__ u; } ;
struct TYPE_4__ {struct exit_ctl_data exit_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_PAL_CALL ; 
#define  PAL_BRAND_INFO 130 
#define  PAL_HALT_INFO 129 
#define  PAL_PERF_MON_INFO 128 
 void* kvm_trans_pal_call_args (struct kvm_vcpu*,unsigned long) ; 
 void* vcpu_get_gr (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void set_pal_call_data(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p = &vcpu->arch.exit_data;
	unsigned long gr28 = vcpu_get_gr(vcpu, 28);
	unsigned long gr29 = vcpu_get_gr(vcpu, 29);
	unsigned long gr30 = vcpu_get_gr(vcpu, 30);

	/*FIXME:For static and stacked convention, firmware
	 * has put the parameters in gr28-gr31 before
	 * break to vmm  !!*/

	switch (gr28) {
	case PAL_PERF_MON_INFO:
	case PAL_HALT_INFO:
		p->u.pal_data.gr29 =  kvm_trans_pal_call_args(vcpu, gr29);
		p->u.pal_data.gr30 = vcpu_get_gr(vcpu, 30);
		break;
	case PAL_BRAND_INFO:
		p->u.pal_data.gr29 = gr29;
		p->u.pal_data.gr30 = kvm_trans_pal_call_args(vcpu, gr30);
		break;
	default:
		p->u.pal_data.gr29 = gr29;
		p->u.pal_data.gr30 = vcpu_get_gr(vcpu, 30);
	}
	p->u.pal_data.gr28 = gr28;
	p->u.pal_data.gr31 = vcpu_get_gr(vcpu, 31);

	p->exit_reason = EXIT_REASON_PAL_CALL;
}