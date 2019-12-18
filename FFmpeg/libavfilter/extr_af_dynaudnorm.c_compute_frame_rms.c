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
struct TYPE_3__ {int channels; int nb_samples; scalar_t__* extended_data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  DBL_EPSILON ; 
 double FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pow_2 (double const) ; 
 int /*<<< orphan*/  sqrt (double) ; 

__attribute__((used)) static double compute_frame_rms(AVFrame *frame, int channel)
{
    double rms_value = 0.0;
    int c, i;

    if (channel == -1) {
        for (c = 0; c < frame->channels; c++) {
            const double *data_ptr = (double *)frame->extended_data[c];

            for (i = 0; i < frame->nb_samples; i++) {
                rms_value += pow_2(data_ptr[i]);
            }
        }

        rms_value /= frame->nb_samples * frame->channels;
    } else {
        const double *data_ptr = (double *)frame->extended_data[channel];
        for (i = 0; i < frame->nb_samples; i++) {
            rms_value += pow_2(data_ptr[i]);
        }

        rms_value /= frame->nb_samples;
    }

    return FFMAX(sqrt(rms_value), DBL_EPSILON);
}