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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long VMX_EPT_AD_ENABLE_BIT ; 
 unsigned long VMX_EPT_DEFAULT_GAW ; 
 unsigned long VMX_EPT_DEFAULT_MT ; 
 unsigned long VMX_EPT_GAW_EPTP_SHIFT ; 
 scalar_t__ enable_ept_ad_bits ; 

__attribute__((used)) static u64 construct_eptp(unsigned long root_hpa)
{
	u64 eptp;

	/* TODO write the value reading from MSR */
	eptp = VMX_EPT_DEFAULT_MT |
		VMX_EPT_DEFAULT_GAW << VMX_EPT_GAW_EPTP_SHIFT;
	if (enable_ept_ad_bits)
		eptp |= VMX_EPT_AD_ENABLE_BIT;
	eptp |= (root_hpa & PAGE_MASK);

	return eptp;
}