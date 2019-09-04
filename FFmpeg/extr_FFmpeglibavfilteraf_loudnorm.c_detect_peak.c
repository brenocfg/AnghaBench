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
struct TYPE_3__ {double* limiter_buf; double target_tp; int limiter_buf_index; int limiter_buf_size; scalar_t__ frame_type; double* prev_smp; int peak_index; } ;
typedef  TYPE_1__ LoudNormContext ;

/* Variables and functions */
 scalar_t__ FIRST_FRAME ; 
 double fabs (double) ; 

__attribute__((used)) static void detect_peak(LoudNormContext *s, int offset, int nb_samples, int channels, int *peak_delta, double *peak_value)
{
    int n, c, i, index;
    double ceiling;
    double *buf;

    *peak_delta = -1;
    buf = s->limiter_buf;
    ceiling = s->target_tp;

    index = s->limiter_buf_index + (offset * channels) + (1920 * channels);
    if (index >= s->limiter_buf_size)
        index -= s->limiter_buf_size;

    if (s->frame_type == FIRST_FRAME) {
        for (c = 0; c < channels; c++)
            s->prev_smp[c] = fabs(buf[index + c - channels]);
    }

    for (n = 0; n < nb_samples; n++) {
        for (c = 0; c < channels; c++) {
            double this, next, max_peak;

            this = fabs(buf[(index + c) < s->limiter_buf_size ? (index + c) : (index + c - s->limiter_buf_size)]);
            next = fabs(buf[(index + c + channels) < s->limiter_buf_size ? (index + c + channels) : (index + c + channels - s->limiter_buf_size)]);

            if ((s->prev_smp[c] <= this) && (next <= this) && (this > ceiling) && (n > 0)) {
                int detected;

                detected = 1;
                for (i = 2; i < 12; i++) {
                    next = fabs(buf[(index + c + (i * channels)) < s->limiter_buf_size ? (index + c + (i * channels)) : (index + c + (i * channels) - s->limiter_buf_size)]);
                    if (next > this) {
                        detected = 0;
                        break;
                    }
                }

                if (!detected)
                    continue;

                for (c = 0; c < channels; c++) {
                    if (c == 0 || fabs(buf[index + c]) > max_peak)
                        max_peak = fabs(buf[index + c]);

                    s->prev_smp[c] = fabs(buf[(index + c) < s->limiter_buf_size ? (index + c) : (index + c - s->limiter_buf_size)]);
                }

                *peak_delta = n;
                s->peak_index = index;
                *peak_value = max_peak;
                return;
            }

            s->prev_smp[c] = this;
        }

        index += channels;
        if (index >= s->limiter_buf_size)
            index -= s->limiter_buf_size;
    }
}