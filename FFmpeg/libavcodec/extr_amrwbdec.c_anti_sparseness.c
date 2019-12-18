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
struct TYPE_3__ {scalar_t__ fr_cur_mode; double* pitch_gain; double* fixed_gain; int prev_ir_filter_nr; } ;
typedef  TYPE_1__ AMRWBContext ;

/* Variables and functions */
 int AMRWB_SFR_SIZE ; 
 scalar_t__ MODE_8k85 ; 
 int /*<<< orphan*/  ff_celp_circ_addf (float*,float*,float const*,int,float,int) ; 
 float** ir_filters_lookup ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static float *anti_sparseness(AMRWBContext *ctx,
                              float *fixed_vector, float *buf)
{
    int ir_filter_nr;

    if (ctx->fr_cur_mode > MODE_8k85) // no filtering in higher modes
        return fixed_vector;

    if (ctx->pitch_gain[0] < 0.6) {
        ir_filter_nr = 0;      // strong filtering
    } else if (ctx->pitch_gain[0] < 0.9) {
        ir_filter_nr = 1;      // medium filtering
    } else
        ir_filter_nr = 2;      // no filtering

    /* detect 'onset' */
    if (ctx->fixed_gain[0] > 3.0 * ctx->fixed_gain[1]) {
        if (ir_filter_nr < 2)
            ir_filter_nr++;
    } else {
        int i, count = 0;

        for (i = 0; i < 6; i++)
            if (ctx->pitch_gain[i] < 0.6)
                count++;

        if (count > 2)
            ir_filter_nr = 0;

        if (ir_filter_nr > ctx->prev_ir_filter_nr + 1)
            ir_filter_nr--;
    }

    /* update ir filter strength history */
    ctx->prev_ir_filter_nr = ir_filter_nr;

    ir_filter_nr += (ctx->fr_cur_mode == MODE_8k85);

    if (ir_filter_nr < 2) {
        int i;
        const float *coef = ir_filters_lookup[ir_filter_nr];

        /* Circular convolution code in the reference
         * decoder was modified to avoid using one
         * extra array. The filtered vector is given by:
         *
         * c2(n) = sum(i,0,len-1){ c(i) * coef( (n - i + len) % len ) }
         */

        memset(buf, 0, sizeof(float) * AMRWB_SFR_SIZE);
        for (i = 0; i < AMRWB_SFR_SIZE; i++)
            if (fixed_vector[i])
                ff_celp_circ_addf(buf, buf, coef, i, fixed_vector[i],
                                  AMRWB_SFR_SIZE);
        fixed_vector = buf;
    }

    return fixed_vector;
}