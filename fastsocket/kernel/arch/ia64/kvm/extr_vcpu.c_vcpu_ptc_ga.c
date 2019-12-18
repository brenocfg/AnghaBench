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
typedef  void* u64 ;
struct TYPE_5__ {void* ps; void* vaddr; int /*<<< orphan*/  rr; } ;
struct TYPE_6__ {TYPE_2__ ptc_g_data; } ;
struct exit_ctl_data {TYPE_3__ u; int /*<<< orphan*/  exit_reason; } ;
struct TYPE_4__ {struct exit_ctl_data exit_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_PTC_G ; 
 int /*<<< orphan*/  local_irq_restore (long) ; 
 int /*<<< orphan*/  local_irq_save (long) ; 
 int /*<<< orphan*/  vcpu_get_rr (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  vcpu_ptc_l (struct kvm_vcpu*,void*,void*) ; 
 int /*<<< orphan*/  vmm_transition (struct kvm_vcpu*) ; 

void vcpu_ptc_ga(struct kvm_vcpu *vcpu, u64 va, u64 ps)
{
	struct exit_ctl_data *p = &vcpu->arch.exit_data;
	long psr;
	local_irq_save(psr);
	p->exit_reason = EXIT_REASON_PTC_G;

	p->u.ptc_g_data.rr = vcpu_get_rr(vcpu, va);
	p->u.ptc_g_data.vaddr = va;
	p->u.ptc_g_data.ps = ps;
	vmm_transition(vcpu);
	/* Do Local Purge Here*/
	vcpu_ptc_l(vcpu, va, ps);
	local_irq_restore(psr);
}