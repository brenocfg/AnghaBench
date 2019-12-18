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
 int /*<<< orphan*/  FEATURE_AES ; 
 int /*<<< orphan*/  FEATURE_AVX ; 
 int /*<<< orphan*/  FEATURE_AVX2 ; 
 int /*<<< orphan*/  FEATURE_AVX5124FMAPS ; 
 int /*<<< orphan*/  FEATURE_AVX5124VNNIW ; 
 int /*<<< orphan*/  FEATURE_AVX512BITALG ; 
 int /*<<< orphan*/  FEATURE_AVX512BW ; 
 int /*<<< orphan*/  FEATURE_AVX512CD ; 
 int /*<<< orphan*/  FEATURE_AVX512DQ ; 
 int /*<<< orphan*/  FEATURE_AVX512ER ; 
 int /*<<< orphan*/  FEATURE_AVX512F ; 
 int /*<<< orphan*/  FEATURE_AVX512IFMA ; 
 int /*<<< orphan*/  FEATURE_AVX512PF ; 
 int /*<<< orphan*/  FEATURE_AVX512VBMI ; 
 int /*<<< orphan*/  FEATURE_AVX512VBMI2 ; 
 int /*<<< orphan*/  FEATURE_AVX512VL ; 
 int /*<<< orphan*/  FEATURE_AVX512VNNI ; 
 int /*<<< orphan*/  FEATURE_AVX512VPOPCNTDQ ; 
 int /*<<< orphan*/  FEATURE_BMI ; 
 int /*<<< orphan*/  FEATURE_BMI2 ; 
 int /*<<< orphan*/  FEATURE_CMOV ; 
 int /*<<< orphan*/  FEATURE_FMA ; 
 int /*<<< orphan*/  FEATURE_FMA4 ; 
 int /*<<< orphan*/  FEATURE_GFNI ; 
 int /*<<< orphan*/  FEATURE_MMX ; 
 int /*<<< orphan*/  FEATURE_PCLMUL ; 
 int /*<<< orphan*/  FEATURE_POPCNT ; 
 int /*<<< orphan*/  FEATURE_SSE ; 
 int /*<<< orphan*/  FEATURE_SSE2 ; 
 int /*<<< orphan*/  FEATURE_SSE3 ; 
 int /*<<< orphan*/  FEATURE_SSE4_1 ; 
 int /*<<< orphan*/  FEATURE_SSE4_2 ; 
 int /*<<< orphan*/  FEATURE_SSE4_A ; 
 int /*<<< orphan*/  FEATURE_SSSE3 ; 
 int /*<<< orphan*/  FEATURE_VPCLMULQDQ ; 
 int /*<<< orphan*/  FEATURE_XOP ; 
 int /*<<< orphan*/  getX86CpuIDAndInfo (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  getX86CpuIDAndInfoEx (int,int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  getX86XCR0 (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  setFeature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getAvailableFeatures(unsigned ECX, unsigned EDX, unsigned MaxLeaf,
                                 unsigned *FeaturesOut,
                                 unsigned *Features2Out) {
  unsigned Features = 0;
  unsigned Features2 = 0;
  unsigned EAX, EBX;

#define setFeature(F)                                                          \
  do {                                                                         \
    if (F < 32)                                                                \
      Features |= 1U << (F & 0x1f);                                            \
    else if (F < 64)                                                           \
      Features2 |= 1U << ((F - 32) & 0x1f);                                    \
  } while (0)

  if ((EDX >> 15) & 1)
    setFeature(FEATURE_CMOV);
  if ((EDX >> 23) & 1)
    setFeature(FEATURE_MMX);
  if ((EDX >> 25) & 1)
    setFeature(FEATURE_SSE);
  if ((EDX >> 26) & 1)
    setFeature(FEATURE_SSE2);

  if ((ECX >> 0) & 1)
    setFeature(FEATURE_SSE3);
  if ((ECX >> 1) & 1)
    setFeature(FEATURE_PCLMUL);
  if ((ECX >> 9) & 1)
    setFeature(FEATURE_SSSE3);
  if ((ECX >> 12) & 1)
    setFeature(FEATURE_FMA);
  if ((ECX >> 19) & 1)
    setFeature(FEATURE_SSE4_1);
  if ((ECX >> 20) & 1)
    setFeature(FEATURE_SSE4_2);
  if ((ECX >> 23) & 1)
    setFeature(FEATURE_POPCNT);
  if ((ECX >> 25) & 1)
    setFeature(FEATURE_AES);

  // If CPUID indicates support for XSAVE, XRESTORE and AVX, and XGETBV
  // indicates that the AVX registers will be saved and restored on context
  // switch, then we have full AVX support.
  const unsigned AVXBits = (1 << 27) | (1 << 28);
  bool HasAVX = ((ECX & AVXBits) == AVXBits) && !getX86XCR0(&EAX, &EDX) &&
                ((EAX & 0x6) == 0x6);
  bool HasAVX512Save = HasAVX && ((EAX & 0xe0) == 0xe0);

  if (HasAVX)
    setFeature(FEATURE_AVX);

  bool HasLeaf7 =
      MaxLeaf >= 0x7 && !getX86CpuIDAndInfoEx(0x7, 0x0, &EAX, &EBX, &ECX, &EDX);

  if (HasLeaf7 && ((EBX >> 3) & 1))
    setFeature(FEATURE_BMI);
  if (HasLeaf7 && ((EBX >> 5) & 1) && HasAVX)
    setFeature(FEATURE_AVX2);
  if (HasLeaf7 && ((EBX >> 8) & 1))
    setFeature(FEATURE_BMI2);
  if (HasLeaf7 && ((EBX >> 16) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512F);
  if (HasLeaf7 && ((EBX >> 17) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512DQ);
  if (HasLeaf7 && ((EBX >> 21) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512IFMA);
  if (HasLeaf7 && ((EBX >> 26) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512PF);
  if (HasLeaf7 && ((EBX >> 27) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512ER);
  if (HasLeaf7 && ((EBX >> 28) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512CD);
  if (HasLeaf7 && ((EBX >> 30) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512BW);
  if (HasLeaf7 && ((EBX >> 31) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512VL);

  if (HasLeaf7 && ((ECX >> 1) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512VBMI);
  if (HasLeaf7 && ((ECX >> 6) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512VBMI2);
  if (HasLeaf7 && ((ECX >> 8) & 1))
    setFeature(FEATURE_GFNI);
  if (HasLeaf7 && ((ECX >> 10) & 1) && HasAVX)
    setFeature(FEATURE_VPCLMULQDQ);
  if (HasLeaf7 && ((ECX >> 11) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512VNNI);
  if (HasLeaf7 && ((ECX >> 12) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512BITALG);
  if (HasLeaf7 && ((ECX >> 14) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX512VPOPCNTDQ);

  if (HasLeaf7 && ((EDX >> 2) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX5124VNNIW);
  if (HasLeaf7 && ((EDX >> 3) & 1) && HasAVX512Save)
    setFeature(FEATURE_AVX5124FMAPS);

  unsigned MaxExtLevel;
  getX86CpuIDAndInfo(0x80000000, &MaxExtLevel, &EBX, &ECX, &EDX);

  bool HasExtLeaf1 = MaxExtLevel >= 0x80000001 &&
                     !getX86CpuIDAndInfo(0x80000001, &EAX, &EBX, &ECX, &EDX);
  if (HasExtLeaf1 && ((ECX >> 6) & 1))
    setFeature(FEATURE_SSE4_A);
  if (HasExtLeaf1 && ((ECX >> 11) & 1))
    setFeature(FEATURE_XOP);
  if (HasExtLeaf1 && ((ECX >> 16) & 1))
    setFeature(FEATURE_FMA4);

  *FeaturesOut = Features;
  *Features2Out = Features2;
#undef setFeature
}