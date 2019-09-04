#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_4__ {float (* dot_productf ) (float const*,float const*,scalar_t__) ;} ;
struct TYPE_5__ {scalar_t__ fr_cur_mode; TYPE_1__ celpm_ctx; } ;
typedef  TYPE_2__ AMRWBContext ;

/* Variables and functions */
 scalar_t__ AMRWB_SFR_SIZE ; 
 scalar_t__ MODE_23k85 ; 
 float av_clipf (double,double,double) ; 
 float* qua_hb_gain ; 
 float stub1 (float const*,float const*,scalar_t__) ; 
 float stub2 (float const*,float const*,scalar_t__) ; 

__attribute__((used)) static float find_hb_gain(AMRWBContext *ctx, const float *synth,
                          uint16_t hb_idx, uint8_t vad)
{
    int wsp = (vad > 0);
    float tilt;
    float tmp;

    if (ctx->fr_cur_mode == MODE_23k85)
        return qua_hb_gain[hb_idx] * (1.0f / (1 << 14));

    tmp = ctx->celpm_ctx.dot_productf(synth, synth + 1, AMRWB_SFR_SIZE - 1);

    if (tmp > 0) {
        tilt = tmp / ctx->celpm_ctx.dot_productf(synth, synth, AMRWB_SFR_SIZE);
    } else
        tilt = 0;

    /* return gain bounded by [0.1, 1.0] */
    return av_clipf((1.0 - tilt) * (1.25 - 0.25 * wsp), 0.1, 1.0);
}