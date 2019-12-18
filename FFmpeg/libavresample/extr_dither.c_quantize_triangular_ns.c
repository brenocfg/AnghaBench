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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {scalar_t__ mute_reset_threshold; int* ns_coef_b; int* ns_coef_a; scalar_t__ mute_dither_threshold; } ;
struct TYPE_5__ {float* noise_buf; size_t noise_buf_ptr; scalar_t__ mute; int* dither_a; int* dither_b; } ;
typedef  TYPE_1__ DitherState ;
typedef  TYPE_2__ DitherContext ;

/* Variables and functions */
 float const S16_SCALE ; 
 int /*<<< orphan*/  av_clip_int16 (int /*<<< orphan*/ ) ; 
 int av_clipf (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  lrintf (float) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void quantize_triangular_ns(DitherContext *c, DitherState *state,
                                   int16_t *dst, const float *src,
                                   int nb_samples)
{
    int i, j;
    float *dither = &state->noise_buf[state->noise_buf_ptr];

    if (state->mute > c->mute_reset_threshold)
        memset(state->dither_a, 0, sizeof(state->dither_a));

    for (i = 0; i < nb_samples; i++) {
        float err = 0;
        float sample = src[i] * S16_SCALE;

        for (j = 0; j < 4; j++) {
            err += c->ns_coef_b[j] * state->dither_b[j] -
                   c->ns_coef_a[j] * state->dither_a[j];
        }
        for (j = 3; j > 0; j--) {
            state->dither_a[j] = state->dither_a[j - 1];
            state->dither_b[j] = state->dither_b[j - 1];
        }
        state->dither_a[0] = err;
        sample -= err;

        if (state->mute > c->mute_dither_threshold) {
            dst[i]             = av_clip_int16(lrintf(sample));
            state->dither_b[0] = 0;
        } else {
            dst[i]             = av_clip_int16(lrintf(sample + dither[i]));
            state->dither_b[0] = av_clipf(dst[i] - sample, -1.5f, 1.5f);
        }

        state->mute++;
        if (src[i])
            state->mute = 0;
    }
}