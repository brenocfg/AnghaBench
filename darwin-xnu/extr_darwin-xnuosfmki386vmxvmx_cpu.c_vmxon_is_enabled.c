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
typedef  int boolean_t ;

/* Variables and functions */
 int MSR_IA32_FEATCTL_VMXON ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 scalar_t__ vmx_is_available () ; 

__attribute__((used)) static inline boolean_t
vmxon_is_enabled(void)
{
	return (vmx_is_available() &&
		(rdmsr64(MSR_IA32_FEATURE_CONTROL) & MSR_IA32_FEATCTL_VMXON));
}