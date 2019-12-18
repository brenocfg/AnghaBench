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
struct ExecIFace {int /*<<< orphan*/  (* GetCPUInfoTags ) (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  has_vu ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int CPUTEST_FLAG_ALTIVEC ; 
 int CPU_ALTIVEC ; 
 int CTL_HW ; 
 int CTL_MACHDEP ; 
 int /*<<< orphan*/  GCIT_VectorUnit ; 
 int HW_VECTORUNIT ; 
 int /*<<< orphan*/  TAG_DONE ; 
 scalar_t__ VECTORTYPE_ALTIVEC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_get_cpu_flags_ppc(void)
{
//#if HAVE_ALTIVEC
#if ARCH_POWERPC_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern struct ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    if (result == VECTORTYPE_ALTIVEC)
        return CPUTEST_FLAG_ALTIVEC;
    return 0;
#elif defined(__APPLE__) || defined(__OpenBSD__)
#ifdef __OpenBSD__
    int sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#else
    int sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    int has_vu = 0;
    size_t len = sizeof(has_vu);
    int err;

    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);

    if (err == 0)
        return has_vu ? CPUTEST_FLAG_ALTIVEC : 0;
    return 0;
#elif CONFIG_RUNTIME_CPUDETECT
    int proc_ver;
    // Support of mfspr PVR emulation added in Linux 2.6.17.
    __asm__ volatile("mfspr %0, 287" : "=r" (proc_ver));
    proc_ver >>= 16;
    if (proc_ver  & 0x8000 ||
        proc_ver == 0x000c ||
        proc_ver == 0x0039 || proc_ver == 0x003c ||
        proc_ver == 0x0044 || proc_ver == 0x0045 ||
        proc_ver == 0x0070)
        return CPUTEST_FLAG_ALTIVEC;
    return 0;
#else
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    return CPUTEST_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    return 0;
}