#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* celp_lp_synthesis_filterf ) (float*,float*,float*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {float (* dot_productf ) (float*,float*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* weighted_vector_sumf ) (float*,float*,float const*,double,float,int) ;} ;
struct TYPE_9__ {float* pitch_vector; double* pitch_gain; scalar_t__ fr_cur_mode; TYPE_3__ celpf_ctx; TYPE_2__ celpm_ctx; TYPE_1__ acelpv_ctx; } ;
typedef  TYPE_4__ AMRWBContext ;

/* Variables and functions */
 int AMRWB_SFR_SIZE ; 
 int /*<<< orphan*/  LP_ORDER ; 
 scalar_t__ MODE_8k85 ; 
 int /*<<< orphan*/  ff_scale_vector_to_given_sum_of_squares (float*,float*,float,int) ; 
 int /*<<< orphan*/  stub1 (float*,float*,float const*,double,float,int) ; 
 float stub2 (float*,float*,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,float*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synthesis(AMRWBContext *ctx, float *lpc, float *excitation,
                      float fixed_gain, const float *fixed_vector,
                      float *samples)
{
    ctx->acelpv_ctx.weighted_vector_sumf(excitation, ctx->pitch_vector, fixed_vector,
                            ctx->pitch_gain[0], fixed_gain, AMRWB_SFR_SIZE);

    /* emphasize pitch vector contribution in low bitrate modes */
    if (ctx->pitch_gain[0] > 0.5 && ctx->fr_cur_mode <= MODE_8k85) {
        int i;
        float energy = ctx->celpm_ctx.dot_productf(excitation, excitation,
                                                    AMRWB_SFR_SIZE);

        // XXX: Weird part in both ref code and spec. A unknown parameter
        // {beta} seems to be identical to the current pitch gain
        float pitch_factor = 0.25 * ctx->pitch_gain[0] * ctx->pitch_gain[0];

        for (i = 0; i < AMRWB_SFR_SIZE; i++)
            excitation[i] += pitch_factor * ctx->pitch_vector[i];

        ff_scale_vector_to_given_sum_of_squares(excitation, excitation,
                                                energy, AMRWB_SFR_SIZE);
    }

    ctx->celpf_ctx.celp_lp_synthesis_filterf(samples, lpc, excitation,
                                 AMRWB_SFR_SIZE, LP_ORDER);
}