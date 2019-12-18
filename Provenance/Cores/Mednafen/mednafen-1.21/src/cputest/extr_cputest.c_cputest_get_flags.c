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
 int checked ; 
 int ff_get_cpu_flags_ppc () ; 
 int ff_get_cpu_flags_x86 () ; 
 int flags ; 

int cputest_get_flags(void)
{
    if (checked)
        return flags;

//    if (ARCH_ARM) flags = ff_get_cpu_flags_arm();
#if ARCH_POWERPC
    flags = ff_get_cpu_flags_ppc();
#endif

#if ARCH_X86
    flags = ff_get_cpu_flags_x86();
#endif

    checked = 1;
    return flags;
}