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
typedef  int uint64_t ;
typedef  int csselr_cache_type ;
typedef  int csselr_cache_level ;

/* Variables and functions */
 int /*<<< orphan*/  ISB_SY ; 
 int /*<<< orphan*/  __builtin_arm_isb (int /*<<< orphan*/ ) ; 

void
machine_write_csselr(csselr_cache_level level, csselr_cache_type type)
{
#if __arm__
	uint32_t csselr = (level | type);
	__builtin_arm_mcr(15,2,csselr,0,0,0);
#else
	uint64_t csselr = (level | type);
	__asm__ volatile("msr	CSSELR_EL1, %0" : : "r" (csselr));
#endif
	__builtin_arm_isb(ISB_SY);
}