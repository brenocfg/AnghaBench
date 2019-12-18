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
struct TYPE_3__ {double* pitch_gain; double prev_sparse_fixed_gain; int ir_filter_onset; int prev_ir_filter_nr; scalar_t__ cur_frame_mode; } ;
typedef  int /*<<< orphan*/  AMRFixed ;
typedef  TYPE_1__ AMRContext ;

/* Variables and functions */
 scalar_t__ MODE_10k2 ; 
 scalar_t__ MODE_7k4 ; 
 scalar_t__ MODE_7k95 ; 
 int /*<<< orphan*/  apply_ir_filter (float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ir_filters_lookup ; 
 int /*<<< orphan*/ * ir_filters_lookup_MODE_7k95 ; 

__attribute__((used)) static const float *anti_sparseness(AMRContext *p, AMRFixed *fixed_sparse,
                                    const float *fixed_vector,
                                    float fixed_gain, float *out)
{
    int ir_filter_nr;

    if (p->pitch_gain[4] < 0.6) {
        ir_filter_nr = 0;      // strong filtering
    } else if (p->pitch_gain[4] < 0.9) {
        ir_filter_nr = 1;      // medium filtering
    } else
        ir_filter_nr = 2;      // no filtering

    // detect 'onset'
    if (fixed_gain > 2.0 * p->prev_sparse_fixed_gain) {
        p->ir_filter_onset = 2;
    } else if (p->ir_filter_onset)
        p->ir_filter_onset--;

    if (!p->ir_filter_onset) {
        int i, count = 0;

        for (i = 0; i < 5; i++)
            if (p->pitch_gain[i] < 0.6)
                count++;
        if (count > 2)
            ir_filter_nr = 0;

        if (ir_filter_nr > p->prev_ir_filter_nr + 1)
            ir_filter_nr--;
    } else if (ir_filter_nr < 2)
        ir_filter_nr++;

    // Disable filtering for very low level of fixed_gain.
    // Note this step is not specified in the technical description but is in
    // the reference source in the function Ph_disp.
    if (fixed_gain < 5.0)
        ir_filter_nr = 2;

    if (p->cur_frame_mode != MODE_7k4 && p->cur_frame_mode < MODE_10k2
         && ir_filter_nr < 2) {
        apply_ir_filter(out, fixed_sparse,
                        (p->cur_frame_mode == MODE_7k95 ?
                             ir_filters_lookup_MODE_7k95 :
                             ir_filters_lookup)[ir_filter_nr]);
        fixed_vector = out;
    }

    // update ir filter strength history
    p->prev_ir_filter_nr       = ir_filter_nr;
    p->prev_sparse_fixed_gain  = fixed_gain;

    return fixed_vector;
}