#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float* gain_tab1; int loc_scale; float* gain_tab2; int id2exp_offset; int loc_size; } ;
struct TYPE_6__ {int num_points; size_t* lev_code; int* loc_code; } ;
typedef  TYPE_1__ AtracGainInfo ;
typedef  TYPE_2__ AtracGCContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 

void ff_atrac_gain_compensation(AtracGCContext *gctx, float *in, float *prev,
                                AtracGainInfo *gc_now, AtracGainInfo *gc_next,
                                int num_samples, float *out)
{
    float lev, gc_scale, gain_inc;
    int i, pos, lastpos;

    gc_scale = gc_next->num_points ? gctx->gain_tab1[gc_next->lev_code[0]]
                                   : 1.0f;

    if (!gc_now->num_points) {
        for (pos = 0; pos < num_samples; pos++)
            out[pos] = in[pos] * gc_scale + prev[pos];
    } else {
        pos = 0;

        for (i = 0; i < gc_now->num_points; i++) {
            lastpos = gc_now->loc_code[i] << gctx->loc_scale;

            lev = gctx->gain_tab1[gc_now->lev_code[i]];
            gain_inc = gctx->gain_tab2[(i + 1 < gc_now->num_points ? gc_now->lev_code[i + 1]
                                                                   : gctx->id2exp_offset) -
                                       gc_now->lev_code[i] + 15];

            /* apply constant gain level and overlap */
            for (; pos < lastpos; pos++)
                out[pos] = (in[pos] * gc_scale + prev[pos]) * lev;

            /* interpolate between two different gain levels */
            for (; pos < lastpos + gctx->loc_size; pos++) {
                out[pos] = (in[pos] * gc_scale + prev[pos]) * lev;
                lev *= gain_inc;
            }
        }

        for (; pos < num_samples; pos++)
            out[pos] = in[pos] * gc_scale + prev[pos];
    }

    /* copy the overlapping part into the delay buffer */
    memcpy(prev, &in[num_samples], num_samples * sizeof(float));
}