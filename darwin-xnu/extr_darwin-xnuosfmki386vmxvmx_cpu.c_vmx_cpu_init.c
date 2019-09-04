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
struct TYPE_5__ {int initialized; int vmx_present; void* cr4_fixed_1; void* cr4_fixed_0; void* cr0_fixed_1; void* cr0_fixed_0; void* vmcs_id; } ;
typedef  TYPE_2__ vmx_specs_t ;
typedef  void* uint32_t ;
struct TYPE_4__ {TYPE_2__ specs; } ;
struct TYPE_6__ {TYPE_1__ cpu_vmx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_VMX_BASIC ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR0_FIXED0 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR0_FIXED1 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR4_FIXED0 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR4_FIXED1 ; 
 int TRUE ; 
 int /*<<< orphan*/  VMX_KPRINTF (char*,int /*<<< orphan*/ ,int) ; 
 int VMX_VCR_VMCS_REV_ID ; 
 int /*<<< orphan*/  cpu_number () ; 
 TYPE_3__* current_cpu_datap () ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_enable () ; 
 scalar_t__ vmx_is_available () ; 
 scalar_t__ vmxon_is_enabled () ; 

void
vmx_cpu_init()
{
	vmx_specs_t *specs = &current_cpu_datap()->cpu_vmx.specs;

	vmx_enable();

	VMX_KPRINTF("[%d]vmx_cpu_init() initialized: %d\n",
		    cpu_number(), specs->initialized);

	/* if we have read the data on boot, we won't read it again on wakeup */
	if (specs->initialized)
		return;
	else
		specs->initialized = TRUE;

	/* See if VMX is present, return if it is not */
	specs->vmx_present = vmx_is_available() && vmxon_is_enabled();
	VMX_KPRINTF("[%d]vmx_cpu_init() vmx_present: %d\n",
		    cpu_number(), specs->vmx_present);
	if (!specs->vmx_present)
		return;

#define rdmsr_mask(msr, mask) (uint32_t)(rdmsr64(msr) & (mask))
	specs->vmcs_id = rdmsr_mask(MSR_IA32_VMX_BASIC, VMX_VCR_VMCS_REV_ID);

	/* Obtain VMX-fixed bits in CR0 */
	specs->cr0_fixed_0 = rdmsr_mask(MSR_IA32_VMX_CR0_FIXED0, 0xFFFFFFFF);
	specs->cr0_fixed_1 = rdmsr_mask(MSR_IA32_VMX_CR0_FIXED1, 0xFFFFFFFF);
	
	/* Obtain VMX-fixed bits in CR4 */
	specs->cr4_fixed_0 = rdmsr_mask(MSR_IA32_VMX_CR4_FIXED0, 0xFFFFFFFF);
	specs->cr4_fixed_1 = rdmsr_mask(MSR_IA32_VMX_CR4_FIXED1, 0xFFFFFFFF);
}