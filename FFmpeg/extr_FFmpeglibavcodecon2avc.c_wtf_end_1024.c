#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* fft_calc ) (TYPE_4__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* fft_permute ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* fft_calc ) (TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* fft_permute ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {TYPE_3__ fft1024; TYPE_4__ fft256; } ;
typedef  TYPE_1__ On2AVCContext ;
typedef  int /*<<< orphan*/  FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  combine_fft (float*,float*,float*,float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ff_on2avc_ctab_1 ; 
 int /*<<< orphan*/  ff_on2avc_ctab_2 ; 
 int /*<<< orphan*/  ff_on2avc_ctab_3 ; 
 int /*<<< orphan*/  ff_on2avc_ctab_4 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_1 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_2 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_3 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_4 ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  pretwiddle (float*,float*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_head_and_tail (float*,int,int,int) ; 

__attribute__((used)) static void wtf_end_1024(On2AVCContext *c, float *out, float *src,
                         float *tmp0, float *tmp1)
{
    memcpy(src,        tmp0,      768 * sizeof(*tmp0));
    memcpy(tmp0 + 768, src + 768, 256 * sizeof(*tmp0));

    zero_head_and_tail(src,       256, 16, 4);
    zero_head_and_tail(src + 256, 256, 16, 4);
    zero_head_and_tail(src + 512, 256, 13, 7);
    zero_head_and_tail(src + 768, 256, 15, 5);

    c->fft256.fft_permute(&c->fft256, (FFTComplex*)src);
    c->fft256.fft_permute(&c->fft256, (FFTComplex*)(src + 256));
    c->fft256.fft_permute(&c->fft256, (FFTComplex*)(src + 512));
    c->fft256.fft_permute(&c->fft256, (FFTComplex*)(src + 768));
    c->fft256.fft_calc(&c->fft256, (FFTComplex*)src);
    c->fft256.fft_calc(&c->fft256, (FFTComplex*)(src + 256));
    c->fft256.fft_calc(&c->fft256, (FFTComplex*)(src + 512));
    c->fft256.fft_calc(&c->fft256, (FFTComplex*)(src + 768));
    combine_fft(src, src + 256, src + 512, src + 768, tmp1,
                ff_on2avc_ctab_1, ff_on2avc_ctab_2,
                ff_on2avc_ctab_3, ff_on2avc_ctab_4, 1024, 1);
    c->fft1024.fft_permute(&c->fft1024, (FFTComplex*)tmp1);
    c->fft1024.fft_calc(&c->fft1024, (FFTComplex*)tmp1);

    pretwiddle(&tmp0[  0], tmp1, 1024, 84, 4, 16, 4, ff_on2avc_tabs_20_84_1);
    pretwiddle(&tmp0[256], tmp1, 1024, 84, 4, 16, 4, ff_on2avc_tabs_20_84_2);
    pretwiddle(&tmp0[512], tmp1, 1024, 84, 4, 13, 7, ff_on2avc_tabs_20_84_3);
    pretwiddle(&tmp0[768], tmp1, 1024, 84, 4, 15, 5, ff_on2avc_tabs_20_84_4);

    memcpy(src, tmp1, 1024 * sizeof(float));
}