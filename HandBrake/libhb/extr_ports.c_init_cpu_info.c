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
struct TYPE_2__ {char* name; int* buf4; char* buf; int /*<<< orphan*/  platform; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int AV_CPU_FLAG_SSE ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_BDW ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_BNL ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_CHT ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_HSW ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_ICL ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_IVB ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_KBL ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_SKL ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_SLM ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_INTEL_SNB ; 
 int /*<<< orphan*/  HB_CPU_PLATFORM_UNSPECIFIED ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 TYPE_1__ hb_cpu_info ; 
 int /*<<< orphan*/  init_cpu_count () ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static void init_cpu_info()
{
    hb_cpu_info.name     = NULL;
    hb_cpu_info.count    = init_cpu_count();
    hb_cpu_info.platform = HB_CPU_PLATFORM_UNSPECIFIED;

    if (av_get_cpu_flags() & AV_CPU_FLAG_SSE)
    {
#if ARCH_X86_64 || ARCH_X86_32
        int eax, ebx, ecx, edx, family, model;

        cpuid(1, &eax, &ebx, &ecx, &edx);
        family = ((eax >> 8) & 0xf) + ((eax >> 20) & 0xff);
        model  = ((eax >> 4) & 0xf) + ((eax >> 12) & 0xf0);

        // Intel 64 and IA-32 Architectures Software Developer's Manual, Volume 4/January 2019
        // Table 2-1. CPUID Signature Values of DisplayFamily_DisplayModel
        switch (family)
        {
            case 0x06:
            {
                switch (model)
                {
                    case 0x1C:
                    case 0x26:
                    case 0x27:
                    case 0x35:
                    case 0x36:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_BNL;
                        break;
                    case 0x2A:
                    case 0x2D:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_SNB;
                        break;
                    case 0x3A:
                    case 0x3E:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_IVB;
                        break;
                    case 0x37:
                    case 0x4A:
                    case 0x4D:
                    case 0x5A:
                    case 0x5D:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_SLM;
                        break;
                    case 0x3C:
                    case 0x3F:
                    case 0x45:
                    case 0x46:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_HSW;
                        break;
                    case 0x3D:
                    case 0x4F:
                    case 0x56:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_BDW;
                        break;
                    case 0x4C:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_CHT;
                        break;
                    case 0x4E:
                    case 0x5E:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_SKL;
                        break;
                    case 0x8E:
                    case 0x9E:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_KBL;
                        break;
                    case 0x7E:
                        hb_cpu_info.platform = HB_CPU_PLATFORM_INTEL_ICL;
                    default:
                        break;
                }
            } break;

            default:
                break;
        }

        // Intel 64 and IA-32 Architectures Software Developer's Manual, Vol. 2A
        // Figure 3-8: Determination of Support for the Processor Brand String
        // Table 3-17: Information Returned by CPUID Instruction
        cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
        if ((eax & 0x80000004) < 0x80000004)
        {
            cpuid(0x80000002,
                  &hb_cpu_info.buf4[ 0],
                  &hb_cpu_info.buf4[ 1],
                  &hb_cpu_info.buf4[ 2],
                  &hb_cpu_info.buf4[ 3]);
            cpuid(0x80000003,
                  &hb_cpu_info.buf4[ 4],
                  &hb_cpu_info.buf4[ 5],
                  &hb_cpu_info.buf4[ 6],
                  &hb_cpu_info.buf4[ 7]);
            cpuid(0x80000004,
                  &hb_cpu_info.buf4[ 8],
                  &hb_cpu_info.buf4[ 9],
                  &hb_cpu_info.buf4[10],
                  &hb_cpu_info.buf4[11]);

            hb_cpu_info.name    = hb_cpu_info.buf;
            hb_cpu_info.buf[47] = '\0'; // just in case

            while (isspace(*hb_cpu_info.name))
            {
                // skip leading whitespace to prettify
                hb_cpu_info.name++;
            }
        }
#endif // ARCH_X86_64 || ARCH_X86_32
    }
}