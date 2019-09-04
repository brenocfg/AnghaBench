#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double nb_samples; scalar_t__* extended_data; } ;
struct TYPE_5__ {int channels; double* dc_correction_value; int /*<<< orphan*/  fade_factors; int /*<<< orphan*/ * gain_history_original; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int cqueue_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ fade (double,double,int,int /*<<< orphan*/ ) ; 
 double update_value (double,double,double) ; 

__attribute__((used)) static void perform_dc_correction(DynamicAudioNormalizerContext *s, AVFrame *frame)
{
    const double diff = 1.0 / frame->nb_samples;
    int is_first_frame = cqueue_empty(s->gain_history_original[0]);
    int c, i;

    for (c = 0; c < s->channels; c++) {
        double *dst_ptr = (double *)frame->extended_data[c];
        double current_average_value = 0.0;
        double prev_value;

        for (i = 0; i < frame->nb_samples; i++)
            current_average_value += dst_ptr[i] * diff;

        prev_value = is_first_frame ? current_average_value : s->dc_correction_value[c];
        s->dc_correction_value[c] = is_first_frame ? current_average_value : update_value(current_average_value, s->dc_correction_value[c], 0.1);

        for (i = 0; i < frame->nb_samples; i++) {
            dst_ptr[i] -= fade(prev_value, s->dc_correction_value[c], i, s->fade_factors);
        }
    }
}