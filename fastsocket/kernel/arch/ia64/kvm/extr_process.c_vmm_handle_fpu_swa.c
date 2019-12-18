#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {unsigned long cr_iip; int /*<<< orphan*/  cr_ifs; int /*<<< orphan*/  pr; int /*<<< orphan*/  ar_fpsr; int /*<<< orphan*/  cr_ipsr; } ;
struct TYPE_7__ {unsigned long status; } ;
typedef  TYPE_1__ fpswa_ret_t ;
struct TYPE_9__ {scalar_t__ ri; } ;
struct TYPE_8__ {int /*<<< orphan*/ * i64; } ;
typedef  TYPE_2__ IA64_BUNDLE ;

/* Variables and functions */
 unsigned long EACCES ; 
 unsigned long EAGAIN ; 
 struct kvm_vcpu* current_vcpu ; 
 scalar_t__ fetch_code (struct kvm_vcpu*,unsigned long,TYPE_2__*) ; 
 TYPE_5__* ia64_psr (struct kvm_pt_regs*) ; 
 TYPE_1__ vmm_fp_emulate (int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct kvm_pt_regs*) ; 

unsigned long vmm_handle_fpu_swa(int fp_fault, struct kvm_pt_regs *regs,
					unsigned long isr)
{
	struct kvm_vcpu *v = current_vcpu;
	IA64_BUNDLE bundle;
	unsigned long fault_ip;
	fpswa_ret_t ret;

	fault_ip = regs->cr_iip;
	/*
	 * When the FP trap occurs, the trapping instruction is completed.
	 * If ipsr.ri == 0, there is the trapping instruction in previous
	 * bundle.
	 */
	if (!fp_fault && (ia64_psr(regs)->ri == 0))
		fault_ip -= 16;

	if (fetch_code(v, fault_ip, &bundle))
		return -EAGAIN;

	if (!bundle.i64[0] && !bundle.i64[1])
		return -EACCES;

	ret = vmm_fp_emulate(fp_fault, &bundle, &regs->cr_ipsr, &regs->ar_fpsr,
			&isr, &regs->pr, &regs->cr_ifs, regs);
	return ret.status;
}