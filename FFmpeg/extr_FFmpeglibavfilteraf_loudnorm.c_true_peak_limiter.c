#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* limiter_buf; double target_tp; int limiter_buf_index; scalar_t__ frame_type; double* gain_reduction; int limiter_state; int env_cnt; int attack_length; int env_index; int limiter_buf_size; int release_length; int /*<<< orphan*/  peak_index; } ;
typedef  TYPE_1__ LoudNormContext ;

/* Variables and functions */
#define  ATTACK 131 
 scalar_t__ FIRST_FRAME ; 
#define  OUT 130 
#define  RELEASE 129 
#define  SUSTAIN 128 
 int /*<<< orphan*/  detect_peak (TYPE_1__*,int,int,int,int*,double*) ; 
 double fabs (double) ; 

__attribute__((used)) static void true_peak_limiter(LoudNormContext *s, double *out, int nb_samples, int channels)
{
    int n, c, index, peak_delta, smp_cnt;
    double ceiling, peak_value;
    double *buf;

    buf = s->limiter_buf;
    ceiling = s->target_tp;
    index = s->limiter_buf_index;
    smp_cnt = 0;

    if (s->frame_type == FIRST_FRAME) {
        double max;

        max = 0.;
        for (n = 0; n < 1920; n++) {
            for (c = 0; c < channels; c++) {
              max = fabs(buf[c]) > max ? fabs(buf[c]) : max;
            }
            buf += channels;
        }

        if (max > ceiling) {
            s->gain_reduction[1] = ceiling / max;
            s->limiter_state = SUSTAIN;
            buf = s->limiter_buf;

            for (n = 0; n < 1920; n++) {
                for (c = 0; c < channels; c++) {
                    double env;
                    env = s->gain_reduction[1];
                    buf[c] *= env;
                }
                buf += channels;
            }
        }

        buf = s->limiter_buf;
    }

    do {

        switch(s->limiter_state) {
        case OUT:
            detect_peak(s, smp_cnt, nb_samples - smp_cnt, channels, &peak_delta, &peak_value);
            if (peak_delta != -1) {
                s->env_cnt = 0;
                smp_cnt += (peak_delta - s->attack_length);
                s->gain_reduction[0] = 1.;
                s->gain_reduction[1] = ceiling / peak_value;
                s->limiter_state = ATTACK;

                s->env_index = s->peak_index - (s->attack_length * channels);
                if (s->env_index < 0)
                    s->env_index += s->limiter_buf_size;

                s->env_index += (s->env_cnt * channels);
                if (s->env_index > s->limiter_buf_size)
                    s->env_index -= s->limiter_buf_size;

            } else {
                smp_cnt = nb_samples;
            }
            break;

        case ATTACK:
            for (; s->env_cnt < s->attack_length; s->env_cnt++) {
                for (c = 0; c < channels; c++) {
                    double env;
                    env = s->gain_reduction[0] - ((double) s->env_cnt / (s->attack_length - 1) * (s->gain_reduction[0] - s->gain_reduction[1]));
                    buf[s->env_index + c] *= env;
                }

                s->env_index += channels;
                if (s->env_index >= s->limiter_buf_size)
                    s->env_index -= s->limiter_buf_size;

                smp_cnt++;
                if (smp_cnt >= nb_samples) {
                    s->env_cnt++;
                    break;
                }
            }

            if (smp_cnt < nb_samples) {
                s->env_cnt = 0;
                s->attack_length = 1920;
                s->limiter_state = SUSTAIN;
            }
            break;

        case SUSTAIN:
            detect_peak(s, smp_cnt, nb_samples, channels, &peak_delta, &peak_value);
            if (peak_delta == -1) {
                s->limiter_state = RELEASE;
                s->gain_reduction[0] = s->gain_reduction[1];
                s->gain_reduction[1] = 1.;
                s->env_cnt = 0;
                break;
            } else {
                double gain_reduction;
                gain_reduction = ceiling / peak_value;

                if (gain_reduction < s->gain_reduction[1]) {
                    s->limiter_state = ATTACK;

                    s->attack_length = peak_delta;
                    if (s->attack_length <= 1)
                        s->attack_length =  2;

                    s->gain_reduction[0] = s->gain_reduction[1];
                    s->gain_reduction[1] = gain_reduction;
                    s->env_cnt = 0;
                    break;
                }

                for (s->env_cnt = 0; s->env_cnt < peak_delta; s->env_cnt++) {
                    for (c = 0; c < channels; c++) {
                        double env;
                        env = s->gain_reduction[1];
                        buf[s->env_index + c] *= env;
                    }

                    s->env_index += channels;
                    if (s->env_index >= s->limiter_buf_size)
                        s->env_index -= s->limiter_buf_size;

                    smp_cnt++;
                    if (smp_cnt >= nb_samples) {
                        s->env_cnt++;
                        break;
                    }
                }
            }
            break;

        case RELEASE:
            for (; s->env_cnt < s->release_length; s->env_cnt++) {
                for (c = 0; c < channels; c++) {
                    double env;
                    env = s->gain_reduction[0] + (((double) s->env_cnt / (s->release_length - 1)) * (s->gain_reduction[1] - s->gain_reduction[0]));
                    buf[s->env_index + c] *= env;
                }

                s->env_index += channels;
                if (s->env_index >= s->limiter_buf_size)
                    s->env_index -= s->limiter_buf_size;

                smp_cnt++;
                if (smp_cnt >= nb_samples) {
                    s->env_cnt++;
                    break;
                }
            }

            if (smp_cnt < nb_samples) {
                s->env_cnt = 0;
                s->limiter_state = OUT;
            }

            break;
        }

    } while (smp_cnt < nb_samples);

    for (n = 0; n < nb_samples; n++) {
        for (c = 0; c < channels; c++) {
            out[c] = buf[index + c];
            if (fabs(out[c]) > ceiling) {
                out[c] = ceiling * (out[c] < 0 ? -1 : 1);
            }
        }
        out += channels;
        index += channels;
        if (index >= s->limiter_buf_size)
            index -= s->limiter_buf_size;
    }
}