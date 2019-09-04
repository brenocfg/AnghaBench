#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* celp_lp_zero_synthesis_filterf ) (float*,float*,float*,int,int) ;int /*<<< orphan*/  (* celp_lp_synthesis_filterf ) (float*,float*,float*,int,int) ;} ;
struct TYPE_6__ {float (* dot_productf ) (float*,float*,int) ;} ;
struct TYPE_8__ {float* samples_in; scalar_t__ cur_frame_mode; float* postfilter_mem; int /*<<< orphan*/  postfilter_agc; int /*<<< orphan*/  tilt_mem; TYPE_2__ celpf_ctx; TYPE_1__ celpm_ctx; } ;
typedef  TYPE_3__ AMRContext ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_AGC_ALPHA ; 
 int AMR_SUBFRAME_SIZE ; 
 int LP_FILTER_ORDER ; 
 scalar_t__ MODE_10k2 ; 
 scalar_t__ MODE_12k2 ; 
 int /*<<< orphan*/  ff_adaptive_gain_control (float*,float*,float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 float* ff_pow_0_55 ; 
 float* ff_pow_0_7 ; 
 float* ff_pow_0_75 ; 
 int /*<<< orphan*/  ff_tilt_compensation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 float stub1 (float*,float*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,float*,int,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,float*,int,int) ; 
 int /*<<< orphan*/  tilt_factor (TYPE_3__*,float*,float*) ; 

__attribute__((used)) static void postfilter(AMRContext *p, float *lpc, float *buf_out)
{
    int i;
    float *samples          = p->samples_in + LP_FILTER_ORDER; // Start of input

    float speech_gain       = p->celpm_ctx.dot_productf(samples, samples,
                                                           AMR_SUBFRAME_SIZE);

    float pole_out[AMR_SUBFRAME_SIZE + LP_FILTER_ORDER];  // Output of pole filter
    const float *gamma_n, *gamma_d;                       // Formant filter factor table
    float lpc_n[LP_FILTER_ORDER], lpc_d[LP_FILTER_ORDER]; // Transfer function coefficients

    if (p->cur_frame_mode == MODE_12k2 || p->cur_frame_mode == MODE_10k2) {
        gamma_n = ff_pow_0_7;
        gamma_d = ff_pow_0_75;
    } else {
        gamma_n = ff_pow_0_55;
        gamma_d = ff_pow_0_7;
    }

    for (i = 0; i < LP_FILTER_ORDER; i++) {
         lpc_n[i] = lpc[i] * gamma_n[i];
         lpc_d[i] = lpc[i] * gamma_d[i];
    }

    memcpy(pole_out, p->postfilter_mem, sizeof(float) * LP_FILTER_ORDER);
    p->celpf_ctx.celp_lp_synthesis_filterf(pole_out + LP_FILTER_ORDER, lpc_d, samples,
                                 AMR_SUBFRAME_SIZE, LP_FILTER_ORDER);
    memcpy(p->postfilter_mem, pole_out + AMR_SUBFRAME_SIZE,
           sizeof(float) * LP_FILTER_ORDER);

    p->celpf_ctx.celp_lp_zero_synthesis_filterf(buf_out, lpc_n,
                                      pole_out + LP_FILTER_ORDER,
                                      AMR_SUBFRAME_SIZE, LP_FILTER_ORDER);

    ff_tilt_compensation(&p->tilt_mem, tilt_factor(p, lpc_n, lpc_d), buf_out,
                         AMR_SUBFRAME_SIZE);

    ff_adaptive_gain_control(buf_out, buf_out, speech_gain, AMR_SUBFRAME_SIZE,
                             AMR_AGC_ALPHA, &p->postfilter_agc);
}