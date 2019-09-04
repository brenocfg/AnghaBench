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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSR_IA32_VMX_BASIC ; 
 int /*<<< orphan*/  MSR_IA32_VMX_PROCBASED_CTLS2 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_TRUE_PROCBASED_CTLS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VMX_BASIC_TRUE_CTLS ; 
 int /*<<< orphan*/  VMX_CAP (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMX_PROCBASED_CTLS2_EPT ; 
 int /*<<< orphan*/  VMX_PROCBASED_CTLS2_UNRESTRICTED ; 
 int /*<<< orphan*/  VMX_TRUE_PROCBASED_SECONDARY_CTLS ; 
 int /*<<< orphan*/  vmx_is_available () ; 

boolean_t
vmx_hv_support()
{
	if (!vmx_is_available())
		return FALSE;

#define CHK(msr, shift, mask) if (!VMX_CAP(msr, shift, mask)) return FALSE;

	/* 'EPT' and 'Unrestricted Mode' are part of the secondary processor-based
	 * VM-execution controls */
	CHK(MSR_IA32_VMX_BASIC, 0, VMX_BASIC_TRUE_CTLS)
	CHK(MSR_IA32_VMX_TRUE_PROCBASED_CTLS, 32, VMX_TRUE_PROCBASED_SECONDARY_CTLS)

	/* if we have these, check for 'EPT' and 'Unrestricted Mode' */
	CHK(MSR_IA32_VMX_PROCBASED_CTLS2, 32, VMX_PROCBASED_CTLS2_EPT)
	CHK(MSR_IA32_VMX_PROCBASED_CTLS2, 32, VMX_PROCBASED_CTLS2_UNRESTRICTED)

	return TRUE;
}