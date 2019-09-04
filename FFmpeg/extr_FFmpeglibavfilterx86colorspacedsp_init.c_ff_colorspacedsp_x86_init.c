#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  multiply3x3; int /*<<< orphan*/ ** rgb2yuv; int /*<<< orphan*/ ** yuv2rgb; int /*<<< orphan*/ *** yuv2yuv; } ;
typedef  TYPE_1__ ColorSpaceDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86_64 ; 
 size_t BPP_10 ; 
 size_t BPP_12 ; 
 size_t BPP_8 ; 
 scalar_t__ EXTERNAL_SSE2 (int) ; 
 size_t SS_420 ; 
 size_t SS_422 ; 
 size_t SS_444 ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  ff_multiply3x3_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_420p10_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_420p12_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_420p8_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_422p10_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_422p12_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_422p8_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_444p10_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_444p12_sse2 ; 
 int /*<<< orphan*/  ff_rgb2yuv_444p8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_420p10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_420p12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_420p8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_422p10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_422p12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_422p8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_444p10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_444p12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2rgb_444p8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p10to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p10to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p10to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p12to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p12to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p12to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p8to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p8to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_420p8to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p10to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p10to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p10to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p12to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p12to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p12to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p8to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p8to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_422p8to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p10to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p10to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p10to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p12to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p12to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p12to8_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p8to10_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p8to12_sse2 ; 
 int /*<<< orphan*/  ff_yuv2yuv_444p8to8_sse2 ; 

void ff_colorspacedsp_x86_init(ColorSpaceDSPContext *dsp)
{
    int cpu_flags = av_get_cpu_flags();

    if (ARCH_X86_64 && EXTERNAL_SSE2(cpu_flags)) {
#define assign_yuv2yuv_fns(ss) \
        dsp->yuv2yuv[BPP_8 ][BPP_8 ][SS_##ss] = ff_yuv2yuv_##ss##p8to8_sse2; \
        dsp->yuv2yuv[BPP_8 ][BPP_10][SS_##ss] = ff_yuv2yuv_##ss##p8to10_sse2; \
        dsp->yuv2yuv[BPP_8 ][BPP_12][SS_##ss] = ff_yuv2yuv_##ss##p8to12_sse2; \
        dsp->yuv2yuv[BPP_10][BPP_8 ][SS_##ss] = ff_yuv2yuv_##ss##p10to8_sse2; \
        dsp->yuv2yuv[BPP_10][BPP_10][SS_##ss] = ff_yuv2yuv_##ss##p10to10_sse2; \
        dsp->yuv2yuv[BPP_10][BPP_12][SS_##ss] = ff_yuv2yuv_##ss##p10to12_sse2; \
        dsp->yuv2yuv[BPP_12][BPP_8 ][SS_##ss] = ff_yuv2yuv_##ss##p12to8_sse2; \
        dsp->yuv2yuv[BPP_12][BPP_10][SS_##ss] = ff_yuv2yuv_##ss##p12to10_sse2; \
        dsp->yuv2yuv[BPP_12][BPP_12][SS_##ss] = ff_yuv2yuv_##ss##p12to12_sse2

        assign_yuv2yuv_fns(420);
        assign_yuv2yuv_fns(422);
        assign_yuv2yuv_fns(444);

#define assign_yuv2rgb_fns(ss) \
        dsp->yuv2rgb[BPP_8 ][SS_##ss] = ff_yuv2rgb_##ss##p8_sse2; \
        dsp->yuv2rgb[BPP_10][SS_##ss] = ff_yuv2rgb_##ss##p10_sse2; \
        dsp->yuv2rgb[BPP_12][SS_##ss] = ff_yuv2rgb_##ss##p12_sse2

        assign_yuv2rgb_fns(420);
        assign_yuv2rgb_fns(422);
        assign_yuv2rgb_fns(444);

#define assign_rgb2yuv_fns(ss) \
        dsp->rgb2yuv[BPP_8 ][SS_##ss] = ff_rgb2yuv_##ss##p8_sse2; \
        dsp->rgb2yuv[BPP_10][SS_##ss] = ff_rgb2yuv_##ss##p10_sse2; \
        dsp->rgb2yuv[BPP_12][SS_##ss] = ff_rgb2yuv_##ss##p12_sse2

        assign_rgb2yuv_fns(420);
        assign_rgb2yuv_fns(422);
        assign_rgb2yuv_fns(444);

        dsp->multiply3x3 = ff_multiply3x3_sse2;
    }
}