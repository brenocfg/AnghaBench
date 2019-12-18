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
struct TYPE_2__ {int platform; } ;

/* Variables and functions */
#define  HB_CPU_PLATFORM_INTEL_BDW 137 
#define  HB_CPU_PLATFORM_INTEL_BNL 136 
#define  HB_CPU_PLATFORM_INTEL_CHT 135 
#define  HB_CPU_PLATFORM_INTEL_HSW 134 
#define  HB_CPU_PLATFORM_INTEL_ICL 133 
#define  HB_CPU_PLATFORM_INTEL_IVB 132 
#define  HB_CPU_PLATFORM_INTEL_KBL 131 
#define  HB_CPU_PLATFORM_INTEL_SKL 130 
#define  HB_CPU_PLATFORM_INTEL_SLM 129 
#define  HB_CPU_PLATFORM_INTEL_SNB 128 
 TYPE_1__ hb_cpu_info ; 

const char* hb_get_cpu_platform_name()
{
    switch (hb_cpu_info.platform)
    {
        case HB_CPU_PLATFORM_INTEL_BNL:
            return "Intel microarchitecture Bonnell";
        case HB_CPU_PLATFORM_INTEL_SNB:
            return "Intel microarchitecture Sandy Bridge";
        case HB_CPU_PLATFORM_INTEL_IVB:
            return "Intel microarchitecture Ivy Bridge";
        case HB_CPU_PLATFORM_INTEL_SLM:
            return "Intel microarchitecture Silvermont";
        case HB_CPU_PLATFORM_INTEL_HSW:
            return "Intel microarchitecture Haswell";
        case HB_CPU_PLATFORM_INTEL_BDW:
            return "Intel microarchitecture Broadwell";
        case HB_CPU_PLATFORM_INTEL_SKL:
            return "Intel microarchitecture Skylake";
        case HB_CPU_PLATFORM_INTEL_CHT:
            return "Intel microarchitecture Airmont";
        case HB_CPU_PLATFORM_INTEL_KBL:
            return "Intel microarchitecture Kaby Lake";
        case HB_CPU_PLATFORM_INTEL_ICL:
            return "Intel microarchitecture Ice Lake";
        default:
            return NULL;
    }
}