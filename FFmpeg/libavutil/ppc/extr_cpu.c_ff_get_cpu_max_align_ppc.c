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
 int AV_CPU_FLAG_ALTIVEC ; 
 int AV_CPU_FLAG_POWER8 ; 
 int AV_CPU_FLAG_VSX ; 
 int av_get_cpu_flags () ; 

size_t ff_get_cpu_max_align_ppc(void)
{
    int flags = av_get_cpu_flags();

    if (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        return 16;

    return 8;
}