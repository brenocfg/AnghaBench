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
struct TYPE_6__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_5__ {int channels; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  DBL_EPSILON ; 
 double FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pow_2 (double const) ; 
 int /*<<< orphan*/  sqrt (double) ; 

__attribute__((used)) static double compute_frame_std_dev(DynamicAudioNormalizerContext *s,
                                    AVFrame *frame, int channel)
{
    double variance = 0.0;
    int i, c;

    if (channel == -1) {
        for (c = 0; c < s->channels; c++) {
            const double *data_ptr = (double *)frame->extended_data[c];

            for (i = 0; i < frame->nb_samples; i++) {
                variance += pow_2(data_ptr[i]);  // Assume that MEAN is *zero*
            }
        }
        variance /= (s->channels * frame->nb_samples) - 1;
    } else {
        const double *data_ptr = (double *)frame->extended_data[channel];

        for (i = 0; i < frame->nb_samples; i++) {
            variance += pow_2(data_ptr[i]);      // Assume that MEAN is *zero*
        }
        variance /= frame->nb_samples - 1;
    }

    return FFMAX(sqrt(variance), DBL_EPSILON);
}