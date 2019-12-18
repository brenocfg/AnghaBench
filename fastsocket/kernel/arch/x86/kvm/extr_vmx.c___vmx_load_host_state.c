#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  host_state_reload; } ;
struct TYPE_9__ {TYPE_1__ stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  gs_sel; int /*<<< orphan*/  ldt_sel; scalar_t__ gs_ldt_reload_needed; int /*<<< orphan*/  fs_sel; scalar_t__ fs_reload_needed; scalar_t__ loaded; } ;
struct vcpu_vmx {int /*<<< orphan*/  msr_host_kernel_gs_base; int /*<<< orphan*/  msr_guest_kernel_gs_base; TYPE_4__ vcpu; TYPE_3__ host_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  gs; } ;
struct TYPE_10__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 scalar_t__ is_long_mode (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_load_ldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gs_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_tss () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __vmx_load_host_state(struct vcpu_vmx *vmx)
{
	if (!vmx->host_state.loaded)
		return;

	++vmx->vcpu.stat.host_state_reload;
	vmx->host_state.loaded = 0;
	if (vmx->host_state.fs_reload_needed)
		loadsegment(fs, vmx->host_state.fs_sel);
	if (vmx->host_state.gs_ldt_reload_needed) {
		kvm_load_ldt(vmx->host_state.ldt_sel);
#ifdef CONFIG_X86_64
		load_gs_index(vmx->host_state.gs_sel);
		wrmsrl(MSR_KERNEL_GS_BASE, current->thread.gs);
#else
		loadsegment(gs, vmx->host_state.gs_sel);
#endif
	}
	reload_tss();
#ifdef CONFIG_X86_64
	if (is_long_mode(&vmx->vcpu)) {
		rdmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
		wrmsrl(MSR_KERNEL_GS_BASE, vmx->msr_host_kernel_gs_base);
	}
#endif
}