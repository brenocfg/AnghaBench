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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  has_vu ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 unsigned long AT_HWCAP ; 
 unsigned long AT_HWCAP2 ; 
 unsigned long AT_NULL ; 
 int AV_CPU_FLAG_ALTIVEC ; 
 int AV_CPU_FLAG_POWER8 ; 
 int AV_CPU_FLAG_VSX ; 
 int CPU_ALTIVEC ; 
 int CTL_HW ; 
 int CTL_MACHDEP ; 
 int /*<<< orphan*/  GCIT_VectorUnit ; 
 int HW_VECTORUNIT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned long PPC_FEATURE2_ARCH_2_07 ; 
 unsigned long PPC_FEATURE_HAS_ALTIVEC ; 
 unsigned long PPC_FEATURE_HAS_VSX ; 
 int PVR_CELL_PPU ; 
 int PVR_G4_7400 ; 
 int PVR_G5_970 ; 
 int PVR_G5_970FX ; 
 int PVR_G5_970GX ; 
 int PVR_G5_970MP ; 
 int PVR_POWER6 ; 
 int PVR_POWER7 ; 
 int PVR_POWER8 ; 
 int /*<<< orphan*/  TAG_DONE ; 
 scalar_t__ VECTORTYPE_ALTIVEC ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned long*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_get_cpu_flags_ppc(void)
{
#if HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern struct ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    if (result == VECTORTYPE_ALTIVEC)
        return AV_CPU_FLAG_ALTIVEC;
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
        return has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    return 0;
#elif defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    int i, ret = 0;
    int fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t count;

    if (fd < 0)
        return 0;

    while ((count = read(fd, buf, sizeof(buf))) > 0) {
        for (i = 0; i < count / sizeof(*buf); i += 2) {
            if (buf[i] == AT_NULL)
                goto out;
            if (buf[i] == AT_HWCAP) {
                if (buf[i + 1] & PPC_FEATURE_HAS_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
#ifdef PPC_FEATURE_HAS_VSX
                if (buf[i + 1] & PPC_FEATURE_HAS_VSX)
                    ret |= AV_CPU_FLAG_VSX;
#endif
                if (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            } else if (buf[i] == AT_HWCAP2) {
#ifdef PPC_FEATURE2_ARCH_2_07
                if (buf[i + 1] & PPC_FEATURE2_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
#endif
            }
        }
    }

out:
    close(fd);
    return ret;
#elif CONFIG_RUNTIME_CPUDETECT && defined(__linux__)
#define PVR_G4_7400  0x000C
#define PVR_G5_970   0x0039
#define PVR_G5_970FX 0x003C
#define PVR_G5_970MP 0x0044
#define PVR_G5_970GX 0x0045
#define PVR_POWER6   0x003E
#define PVR_POWER7   0x003F
#define PVR_POWER8   0x004B
#define PVR_CELL_PPU 0x0070
    int ret = 0;
    int proc_ver;
    // Support of mfspr PVR emulation added in Linux 2.6.17.
    __asm__ volatile("mfspr %0, 287" : "=r" (proc_ver));
    proc_ver >>= 16;
    if (proc_ver  & 0x8000 ||
        proc_ver == PVR_G4_7400  ||
        proc_ver == PVR_G5_970   ||
        proc_ver == PVR_G5_970FX ||
        proc_ver == PVR_G5_970MP ||
        proc_ver == PVR_G5_970GX ||
        proc_ver == PVR_POWER6   ||
        proc_ver == PVR_POWER7   ||
        proc_ver == PVR_POWER8   ||
        proc_ver == PVR_CELL_PPU)
        ret = AV_CPU_FLAG_ALTIVEC;
    if (proc_ver == PVR_POWER7 ||
        proc_ver == PVR_POWER8)
        ret |= AV_CPU_FLAG_VSX;
    if (proc_ver == PVR_POWER8)
        ret |= AV_CPU_FLAG_POWER8;

    return ret;
#else
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    return AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    return 0;
}