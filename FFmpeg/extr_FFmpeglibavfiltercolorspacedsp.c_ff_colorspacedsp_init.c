#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  multiply3x3; int /*<<< orphan*/ *** yuv2yuv; int /*<<< orphan*/ ** rgb2yuv_fsb; int /*<<< orphan*/ ** rgb2yuv; int /*<<< orphan*/ ** yuv2rgb; } ;
typedef  TYPE_1__ ColorSpaceDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 size_t BPP_10 ; 
 size_t BPP_12 ; 
 size_t BPP_8 ; 
 size_t SS_420 ; 
 size_t SS_422 ; 
 size_t SS_444 ; 
 int /*<<< orphan*/  ff_colorspacedsp_x86_init (TYPE_1__*) ; 
 int /*<<< orphan*/  multiply3x3_c ; 
 int /*<<< orphan*/  rgb2yuv_420p10_c ; 
 int /*<<< orphan*/  rgb2yuv_420p12_c ; 
 int /*<<< orphan*/  rgb2yuv_420p8_c ; 
 int /*<<< orphan*/  rgb2yuv_422p10_c ; 
 int /*<<< orphan*/  rgb2yuv_422p12_c ; 
 int /*<<< orphan*/  rgb2yuv_422p8_c ; 
 int /*<<< orphan*/  rgb2yuv_444p10_c ; 
 int /*<<< orphan*/  rgb2yuv_444p12_c ; 
 int /*<<< orphan*/  rgb2yuv_444p8_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_420p10_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_420p12_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_420p8_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_422p10_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_422p12_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_422p8_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_444p10_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_444p12_c ; 
 int /*<<< orphan*/  rgb2yuv_fsb_444p8_c ; 
 int /*<<< orphan*/  yuv2rgb_420p10_c ; 
 int /*<<< orphan*/  yuv2rgb_420p12_c ; 
 int /*<<< orphan*/  yuv2rgb_420p8_c ; 
 int /*<<< orphan*/  yuv2rgb_422p10_c ; 
 int /*<<< orphan*/  yuv2rgb_422p12_c ; 
 int /*<<< orphan*/  yuv2rgb_422p8_c ; 
 int /*<<< orphan*/  yuv2rgb_444p10_c ; 
 int /*<<< orphan*/  yuv2rgb_444p12_c ; 
 int /*<<< orphan*/  yuv2rgb_444p8_c ; 
 int /*<<< orphan*/  yuv2yuv_420p10to10_c ; 
 int /*<<< orphan*/  yuv2yuv_420p10to12_c ; 
 int /*<<< orphan*/  yuv2yuv_420p10to8_c ; 
 int /*<<< orphan*/  yuv2yuv_420p12to10_c ; 
 int /*<<< orphan*/  yuv2yuv_420p12to12_c ; 
 int /*<<< orphan*/  yuv2yuv_420p12to8_c ; 
 int /*<<< orphan*/  yuv2yuv_420p8to10_c ; 
 int /*<<< orphan*/  yuv2yuv_420p8to12_c ; 
 int /*<<< orphan*/  yuv2yuv_420p8to8_c ; 
 int /*<<< orphan*/  yuv2yuv_422p10to10_c ; 
 int /*<<< orphan*/  yuv2yuv_422p10to12_c ; 
 int /*<<< orphan*/  yuv2yuv_422p10to8_c ; 
 int /*<<< orphan*/  yuv2yuv_422p12to10_c ; 
 int /*<<< orphan*/  yuv2yuv_422p12to12_c ; 
 int /*<<< orphan*/  yuv2yuv_422p12to8_c ; 
 int /*<<< orphan*/  yuv2yuv_422p8to10_c ; 
 int /*<<< orphan*/  yuv2yuv_422p8to12_c ; 
 int /*<<< orphan*/  yuv2yuv_422p8to8_c ; 
 int /*<<< orphan*/  yuv2yuv_444p10to10_c ; 
 int /*<<< orphan*/  yuv2yuv_444p10to12_c ; 
 int /*<<< orphan*/  yuv2yuv_444p10to8_c ; 
 int /*<<< orphan*/  yuv2yuv_444p12to10_c ; 
 int /*<<< orphan*/  yuv2yuv_444p12to12_c ; 
 int /*<<< orphan*/  yuv2yuv_444p12to8_c ; 
 int /*<<< orphan*/  yuv2yuv_444p8to10_c ; 
 int /*<<< orphan*/  yuv2yuv_444p8to12_c ; 
 int /*<<< orphan*/  yuv2yuv_444p8to8_c ; 

void ff_colorspacedsp_init(ColorSpaceDSPContext *dsp)
{
#define init_yuv2rgb_fn(bit) \
    dsp->yuv2rgb[BPP_##bit][SS_444] = yuv2rgb_444p##bit##_c; \
    dsp->yuv2rgb[BPP_##bit][SS_422] = yuv2rgb_422p##bit##_c; \
    dsp->yuv2rgb[BPP_##bit][SS_420] = yuv2rgb_420p##bit##_c

    init_yuv2rgb_fn( 8);
    init_yuv2rgb_fn(10);
    init_yuv2rgb_fn(12);

#define init_rgb2yuv_fn(bit) \
    dsp->rgb2yuv[BPP_##bit][SS_444] = rgb2yuv_444p##bit##_c; \
    dsp->rgb2yuv[BPP_##bit][SS_422] = rgb2yuv_422p##bit##_c; \
    dsp->rgb2yuv[BPP_##bit][SS_420] = rgb2yuv_420p##bit##_c

    init_rgb2yuv_fn( 8);
    init_rgb2yuv_fn(10);
    init_rgb2yuv_fn(12);

#define init_rgb2yuv_fsb_fn(bit) \
    dsp->rgb2yuv_fsb[BPP_##bit][SS_444] = rgb2yuv_fsb_444p##bit##_c; \
    dsp->rgb2yuv_fsb[BPP_##bit][SS_422] = rgb2yuv_fsb_422p##bit##_c; \
    dsp->rgb2yuv_fsb[BPP_##bit][SS_420] = rgb2yuv_fsb_420p##bit##_c

    init_rgb2yuv_fsb_fn( 8);
    init_rgb2yuv_fsb_fn(10);
    init_rgb2yuv_fsb_fn(12);

#define init_yuv2yuv_fn(idx1, bit1, bit2) \
    dsp->yuv2yuv[idx1][BPP_##bit2][SS_444] = yuv2yuv_444p##bit1##to##bit2##_c; \
    dsp->yuv2yuv[idx1][BPP_##bit2][SS_422] = yuv2yuv_422p##bit1##to##bit2##_c; \
    dsp->yuv2yuv[idx1][BPP_##bit2][SS_420] = yuv2yuv_420p##bit1##to##bit2##_c
#define init_yuv2yuv_fns(bit1) \
    init_yuv2yuv_fn(BPP_##bit1, bit1,  8); \
    init_yuv2yuv_fn(BPP_##bit1, bit1, 10); \
    init_yuv2yuv_fn(BPP_##bit1, bit1, 12)

    init_yuv2yuv_fns( 8);
    init_yuv2yuv_fns(10);
    init_yuv2yuv_fns(12);

    dsp->multiply3x3 = multiply3x3_c;

    if (ARCH_X86)
        ff_colorspacedsp_x86_init(dsp);
}