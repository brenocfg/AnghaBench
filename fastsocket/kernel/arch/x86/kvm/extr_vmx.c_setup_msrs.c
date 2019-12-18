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
struct TYPE_3__ {int shadow_efer; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct vcpu_vmx {int msr_offset_efer; int save_nmsrs; TYPE_2__ vcpu; } ;

/* Variables and functions */
 int EFER_SCE ; 
 int /*<<< orphan*/  MSR_BITMAP ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  MSR_K6_STAR ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SYSCALL_MASK ; 
 int __find_msr_index (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (unsigned long*) ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 scalar_t__ is_long_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  move_msr_up (struct vcpu_vmx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ update_transition_efer (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_load_host_state (struct vcpu_vmx*) ; 
 unsigned long* vmx_msr_bitmap_legacy ; 
 unsigned long* vmx_msr_bitmap_longmode ; 

__attribute__((used)) static void setup_msrs(struct vcpu_vmx *vmx)
{
	int save_nmsrs, index;
	unsigned long *msr_bitmap;

	vmx_load_host_state(vmx);
	save_nmsrs = 0;
#ifdef CONFIG_X86_64
	if (is_long_mode(&vmx->vcpu)) {
		index = __find_msr_index(vmx, MSR_SYSCALL_MASK);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		index = __find_msr_index(vmx, MSR_LSTAR);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		index = __find_msr_index(vmx, MSR_CSTAR);
		if (index >= 0)
			move_msr_up(vmx, index, save_nmsrs++);
		/*
		 * MSR_K6_STAR is only needed on long mode guests, and only
		 * if efer.sce is enabled.
		 */
		index = __find_msr_index(vmx, MSR_K6_STAR);
		if ((index >= 0) && (vmx->vcpu.arch.shadow_efer & EFER_SCE))
			move_msr_up(vmx, index, save_nmsrs++);
	}
#endif
	vmx->msr_offset_efer = index = __find_msr_index(vmx, MSR_EFER);
	if (index >= 0 && update_transition_efer(vmx))
		move_msr_up(vmx, index, save_nmsrs++);

	vmx->save_nmsrs = save_nmsrs;

	if (cpu_has_vmx_msr_bitmap()) {
		if (is_long_mode(&vmx->vcpu))
			msr_bitmap = vmx_msr_bitmap_longmode;
		else
			msr_bitmap = vmx_msr_bitmap_legacy;

		vmcs_write64(MSR_BITMAP, __pa(msr_bitmap));
	}
}