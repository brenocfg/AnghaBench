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
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_PPC ; 
 scalar_t__ ARCH_X86 ; 
 size_t ff_get_cpu_max_align_aarch64 () ; 
 size_t ff_get_cpu_max_align_arm () ; 
 size_t ff_get_cpu_max_align_ppc () ; 
 size_t ff_get_cpu_max_align_x86 () ; 

size_t av_cpu_max_align(void)
{
    if (ARCH_AARCH64)
        return ff_get_cpu_max_align_aarch64();
    if (ARCH_ARM)
        return ff_get_cpu_max_align_arm();
    if (ARCH_PPC)
        return ff_get_cpu_max_align_ppc();
    if (ARCH_X86)
        return ff_get_cpu_max_align_x86();

    return 8;
}