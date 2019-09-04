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
typedef  int uint32_t ;

/* Variables and functions */
 int AV_CPU_FLAG_ARMV5TE ; 
 int AV_CPU_FLAG_ARMV6 ; 
 int AV_CPU_FLAG_ARMV6T2 ; 
 int AV_CPU_FLAG_NEON ; 
 int AV_CPU_FLAG_SETEND ; 
 int AV_CPU_FLAG_VFP ; 
 int AV_CPU_FLAG_VFPV3 ; 
 int AV_CPU_FLAG_VFP_VM ; 
 int CORE_CPU_FLAGS ; 
 int HWCAP_EDSP ; 
 int HWCAP_NEON ; 
 int HWCAP_THUMBEE ; 
 int HWCAP_TLS ; 
 int HWCAP_VFP ; 
 int HWCAP_VFPv3 ; 
 scalar_t__ get_cpuinfo (int*) ; 
 scalar_t__ get_hwcap (int*) ; 

int ff_get_cpu_flags_arm(void)
{
    int flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    if (get_hwcap(&hwcap) < 0)
        if (get_cpuinfo(&hwcap) < 0)
            return flags;

#define check_cap(cap, flag) do {               \
        if (hwcap & HWCAP_ ## cap)              \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } while (0)

    /* No flags explicitly indicate v6 or v6T2 so check others which
       imply support. */
    check_cap(EDSP,    ARMV5TE);
    check_cap(TLS,     ARMV6);
    check_cap(THUMBEE, ARMV6T2);
    check_cap(VFP,     VFP);
    check_cap(VFPv3,   VFPV3);
    check_cap(NEON,    NEON);

    /* The v6 checks above are not reliable so let higher flags
       trickle down. */
    if (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    else if (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    if (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    if ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    return flags;
}