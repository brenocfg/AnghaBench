#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int neon; int neon_hpfp; } ;

/* Variables and functions */
 TYPE_1__ cpuid_mvfp_info ; 

void
machine_do_mvfpid()
{
#if __arm__
	arm_mvfr0_info_t	arm_mvfr0_info;
	arm_mvfr1_info_t	arm_mvfr1_info;

	__asm__ volatile("vmrs	%0, mvfr0":"=r"(arm_mvfr0_info.value));
	__asm__ volatile("vmrs	%0, mvfr1":"=r"(arm_mvfr1_info.value));

	cpuid_mvfp_info.neon = arm_mvfr1_info.bits.SP;
	cpuid_mvfp_info.neon_hpfp = arm_mvfr1_info.bits.HPFP;
#else
	cpuid_mvfp_info.neon = 1;
	cpuid_mvfp_info.neon_hpfp = 1;
#endif /* __arm__ */

}