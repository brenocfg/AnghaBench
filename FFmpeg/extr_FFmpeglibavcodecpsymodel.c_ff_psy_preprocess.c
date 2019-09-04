#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* filter_flt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*,int,float*,int) ;} ;
struct FFPsyPreprocessContext {int /*<<< orphan*/ * fstate; int /*<<< orphan*/  fcoeffs; TYPE_2__ fiir; TYPE_1__* avctx; } ;
struct TYPE_3__ {int frame_size; } ;
typedef  TYPE_2__ FFIIRFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*,int,float*,int) ; 

void ff_psy_preprocess(struct FFPsyPreprocessContext *ctx, float **audio, int channels)
{
    int ch;
    int frame_size = ctx->avctx->frame_size;
    FFIIRFilterContext *iir = &ctx->fiir;

    if (ctx->fstate) {
        for (ch = 0; ch < channels; ch++)
            iir->filter_flt(ctx->fcoeffs, ctx->fstate[ch], frame_size,
                            &audio[ch][frame_size], 1, &audio[ch][frame_size], 1);
    }
}