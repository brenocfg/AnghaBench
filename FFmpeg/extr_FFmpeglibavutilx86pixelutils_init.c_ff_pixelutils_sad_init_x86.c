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
typedef  int /*<<< orphan*/  av_pixelutils_sad_fn ;

/* Variables and functions */
 scalar_t__ EXTERNAL_AVX2_FAST (int) ; 
 scalar_t__ EXTERNAL_MMX (int) ; 
 scalar_t__ EXTERNAL_MMXEXT (int) ; 
 scalar_t__ EXTERNAL_SSE2 (int) ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  ff_pixelutils_sad_16x16_mmxext ; 
 int /*<<< orphan*/  ff_pixelutils_sad_16x16_sse2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_32x32_avx2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_32x32_sse2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_8x8_mmx ; 
 int /*<<< orphan*/  ff_pixelutils_sad_8x8_mmxext ; 
 int /*<<< orphan*/  ff_pixelutils_sad_a_16x16_sse2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_a_32x32_avx2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_a_32x32_sse2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_u_16x16_sse2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_u_32x32_avx2 ; 
 int /*<<< orphan*/  ff_pixelutils_sad_u_32x32_sse2 ; 

void ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, int aligned)
{
    int cpu_flags = av_get_cpu_flags();

    if (EXTERNAL_MMX(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_mmx;
    }

    // The best way to use SSE2 would be to do 2 SADs in parallel,
    // but we'd have to modify the pixelutils API to return SIMD functions.

    // It's probably not faster to shuffle data around
    // to get two lines of 8 pixels into a single 16byte register,
    // so just use the MMX 8x8 version even when SSE2 is available.
    if (EXTERNAL_MMXEXT(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_mmxext;
        sad[3] = ff_pixelutils_sad_16x16_mmxext;
    }

    if (EXTERNAL_SSE2(cpu_flags)) {
        switch (aligned) {
        case 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   break; // src1 unaligned, src2 unaligned
        case 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; break; // src1   aligned, src2 unaligned
        case 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; break; // src1   aligned, src2   aligned
        }
    }

    if (EXTERNAL_SSE2(cpu_flags)) {
        switch (aligned) {
        case 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   break; // src1 unaligned, src2 unaligned
        case 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; break; // src1   aligned, src2 unaligned
        case 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; break; // src1   aligned, src2   aligned
        }
    }

    if (EXTERNAL_AVX2_FAST(cpu_flags)) {
        switch (aligned) {
        case 0: sad[4] = ff_pixelutils_sad_32x32_avx2;   break; // src1 unaligned, src2 unaligned
        case 1: sad[4] = ff_pixelutils_sad_u_32x32_avx2; break; // src1   aligned, src2 unaligned
        case 2: sad[4] = ff_pixelutils_sad_a_32x32_avx2; break; // src1   aligned, src2   aligned
        }
    }
}