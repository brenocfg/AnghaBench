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
typedef  int /*<<< orphan*/  vendor_shuffle ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_SIMD_AES ; 
 int /*<<< orphan*/  RETRO_SIMD_ASIMD ; 
 int /*<<< orphan*/  RETRO_SIMD_AVX ; 
 int /*<<< orphan*/  RETRO_SIMD_AVX2 ; 
 int /*<<< orphan*/  RETRO_SIMD_CMOV ; 
 int /*<<< orphan*/  RETRO_SIMD_MMX ; 
 int /*<<< orphan*/  RETRO_SIMD_MMXEXT ; 
 int /*<<< orphan*/  RETRO_SIMD_MOVBE ; 
 int /*<<< orphan*/  RETRO_SIMD_NEON ; 
 int /*<<< orphan*/  RETRO_SIMD_POPCNT ; 
 int /*<<< orphan*/  RETRO_SIMD_PS ; 
 int /*<<< orphan*/  RETRO_SIMD_SSE ; 
 int /*<<< orphan*/  RETRO_SIMD_SSE2 ; 
 int /*<<< orphan*/  RETRO_SIMD_SSE3 ; 
 int /*<<< orphan*/  RETRO_SIMD_SSE4 ; 
 int /*<<< orphan*/  RETRO_SIMD_SSE42 ; 
 int /*<<< orphan*/  RETRO_SIMD_SSSE3 ; 
 int /*<<< orphan*/  RETRO_SIMD_VFPU ; 
 int /*<<< orphan*/  RETRO_SIMD_VFPV3 ; 
 int /*<<< orphan*/  RETRO_SIMD_VFPV4 ; 
 int /*<<< orphan*/  RETRO_SIMD_VMX ; 
 int /*<<< orphan*/  RETRO_SIMD_VMX128 ; 
 int VENDOR_INTEL_b ; 
 int VENDOR_INTEL_c ; 
 int VENDOR_INTEL_d ; 
 int /*<<< orphan*/  arm_enable_runfast_mode () ; 
 scalar_t__ check_arm_cpu_feature (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 scalar_t__ sysctlbyname (char*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_cpuid (int,int*) ; 
 int xgetbv_x86 (int /*<<< orphan*/ ) ; 

uint64_t cpu_features_get(void)
{
   uint64_t cpu        = 0;
#if defined(CPU_X86) && !defined(__MACH__)
   int vendor_is_intel = 0;
   const int avx_flags = (1 << 27) | (1 << 28);
#endif
#if defined(__MACH__)
   size_t len          = sizeof(size_t);
   if (sysctlbyname("hw.optional.mmx", NULL, &len, NULL, 0) == 0)
   {
      cpu |= RETRO_SIMD_MMX;
      cpu |= RETRO_SIMD_MMXEXT;
   }

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.floatingpoint", NULL, &len, NULL, 0) == 0)
   {
      cpu |= RETRO_SIMD_CMOV;
   }

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.sse", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSE;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.sse2", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSE2;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.sse3", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSE3;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.supplementalsse3", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSSE3;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.sse4_1", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSE4;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.sse4_2", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_SSE42;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.aes", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_AES;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.avx1_0", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_AVX;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.avx2_0", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_AVX2;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.altivec", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_VMX;

   len            = sizeof(size_t);
   if (sysctlbyname("hw.optional.neon", NULL, &len, NULL, 0) == 0)
      cpu |= RETRO_SIMD_NEON;

#elif defined(_XBOX1)
   cpu |= RETRO_SIMD_MMX;
   cpu |= RETRO_SIMD_SSE;
   cpu |= RETRO_SIMD_MMXEXT;
#elif defined(CPU_X86)
   unsigned max_flag   = 0;
   int flags[4];
   int vendor_shuffle[3];
   char vendor[13];
   uint64_t cpu_flags  = 0;
   x86_cpuid(0, flags);
   vendor_shuffle[0] = flags[1];
   vendor_shuffle[1] = flags[3];
   vendor_shuffle[2] = flags[2];

   vendor[0]         = '\0';
   memcpy(vendor, vendor_shuffle, sizeof(vendor_shuffle));

   /* printf("[CPUID]: Vendor: %s\n", vendor); */

   vendor_is_intel = (
         flags[1] == VENDOR_INTEL_b &&
         flags[2] == VENDOR_INTEL_c &&
         flags[3] == VENDOR_INTEL_d);

   max_flag = flags[0];
   if (max_flag < 1) /* Does CPUID not support func = 1? (unlikely ...) */
      return 0;

   x86_cpuid(1, flags);

   if (flags[3] & (1 << 15))
      cpu |= RETRO_SIMD_CMOV;

   if (flags[3] & (1 << 23))
      cpu |= RETRO_SIMD_MMX;

   if (flags[3] & (1 << 25))
   {
      /* SSE also implies MMXEXT (according to FFmpeg source). */
      cpu |= RETRO_SIMD_SSE;
      cpu |= RETRO_SIMD_MMXEXT;
   }

   if (flags[3] & (1 << 26))
      cpu |= RETRO_SIMD_SSE2;

   if (flags[2] & (1 << 0))
      cpu |= RETRO_SIMD_SSE3;

   if (flags[2] & (1 << 9))
      cpu |= RETRO_SIMD_SSSE3;

   if (flags[2] & (1 << 19))
      cpu |= RETRO_SIMD_SSE4;

   if (flags[2] & (1 << 20))
      cpu |= RETRO_SIMD_SSE42;

   if ((flags[2] & (1 << 23)))
      cpu |= RETRO_SIMD_POPCNT;

   if (vendor_is_intel && (flags[2] & (1 << 22)))
      cpu |= RETRO_SIMD_MOVBE;

   if (flags[2] & (1 << 25))
      cpu |= RETRO_SIMD_AES;

   /* Must only perform xgetbv check if we have
    * AVX CPU support (guaranteed to have at least i686). */
   if (((flags[2] & avx_flags) == avx_flags)
         && ((xgetbv_x86(0) & 0x6) == 0x6))
      cpu |= RETRO_SIMD_AVX;

   if (max_flag >= 7)
   {
      x86_cpuid(7, flags);
      if (flags[1] & (1 << 5))
         cpu |= RETRO_SIMD_AVX2;
   }

   x86_cpuid(0x80000000, flags);
   max_flag = flags[0];
   if (max_flag >= 0x80000001u)
   {
      x86_cpuid(0x80000001, flags);
      if (flags[3] & (1 << 23))
         cpu |= RETRO_SIMD_MMX;
      if (flags[3] & (1 << 22))
         cpu |= RETRO_SIMD_MMXEXT;
   }
#elif defined(__linux__)
   if (check_arm_cpu_feature("neon"))
   {
      cpu |= RETRO_SIMD_NEON;
#ifdef __ARM_NEON__
      arm_enable_runfast_mode();
#endif
   }

   if (check_arm_cpu_feature("vfpv3"))
      cpu |= RETRO_SIMD_VFPV3;

   if (check_arm_cpu_feature("vfpv4"))
      cpu |= RETRO_SIMD_VFPV4;

   if (check_arm_cpu_feature("asimd"))
   {
      cpu |= RETRO_SIMD_ASIMD;
#ifdef __ARM_NEON__
      cpu |= RETRO_SIMD_NEON;
      arm_enable_runfast_mode();
#endif
   }

#if 0
    check_arm_cpu_feature("swp");
    check_arm_cpu_feature("half");
    check_arm_cpu_feature("thumb");
    check_arm_cpu_feature("fastmult");
    check_arm_cpu_feature("vfp");
    check_arm_cpu_feature("edsp");
    check_arm_cpu_feature("thumbee");
    check_arm_cpu_feature("tls");
    check_arm_cpu_feature("idiva");
    check_arm_cpu_feature("idivt");
#endif

#elif defined(__ARM_NEON__)
   cpu |= RETRO_SIMD_NEON;
   arm_enable_runfast_mode();
#elif defined(__ALTIVEC__)
   cpu |= RETRO_SIMD_VMX;
#elif defined(XBOX360)
   cpu |= RETRO_SIMD_VMX128;
#elif defined(PSP) || defined(PS2)
   cpu |= RETRO_SIMD_VFPU;
#elif defined(GEKKO)
   cpu |= RETRO_SIMD_PS;
#endif

   return cpu;
}