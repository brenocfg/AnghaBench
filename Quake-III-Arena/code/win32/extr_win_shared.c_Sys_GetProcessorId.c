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

/* Variables and functions */
 int CPUID_AMD_3DNOW ; 
 int CPUID_AXP ; 
 int CPUID_GENERIC ; 
 int CPUID_INTEL_KATMAI ; 
 int CPUID_INTEL_MMX ; 
 int CPUID_INTEL_PENTIUM ; 
 int CPUID_INTEL_UNSUPPORTED ; 
 scalar_t__ Is3DNOW () ; 
 scalar_t__ IsKNI () ; 
 int /*<<< orphan*/  IsMMX () ; 
 int /*<<< orphan*/  IsPentium () ; 

int Sys_GetProcessorId( void )
{
#if defined _M_ALPHA
	return CPUID_AXP;
#elif !defined _M_IX86
	return CPUID_GENERIC;
#else

	// verify we're at least a Pentium or 486 w/ CPUID support
	if ( !IsPentium() )
		return CPUID_INTEL_UNSUPPORTED;

	// check for MMX
	if ( !IsMMX() )
	{
		// Pentium or PPro
		return CPUID_INTEL_PENTIUM;
	}

	// see if we're an AMD 3DNOW! processor
	if ( Is3DNOW() )
	{
		return CPUID_AMD_3DNOW;
	}

	// see if we're an Intel Katmai
	if ( IsKNI() )
	{
		return CPUID_INTEL_KATMAI;
	}

	// by default we're functionally a vanilla Pentium/MMX or P2/MMX
	return CPUID_INTEL_MMX;

#endif
}