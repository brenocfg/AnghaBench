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
 int CPUID_FEATURE_VMX ; 
 int cpuid_features () ; 

__attribute__((used)) static inline boolean_t
vmx_is_available(void)
{
	return (0 != (cpuid_features() & CPUID_FEATURE_VMX));
}