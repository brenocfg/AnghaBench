#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {float* input_levels; int buf_size; float const* window_func_lut; TYPE_1__* input; int /*<<< orphan*/ * rdft; } ;
struct TYPE_5__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ AudioSurroundContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fft_channel(AVFilterContext *ctx, void *arg, int ch, int nb_jobs)
{
    AudioSurroundContext *s = ctx->priv;
    const float level_in = s->input_levels[ch];
    float *dst;
    int n;

    memset(s->input->extended_data[ch] + s->buf_size * sizeof(float), 0, s->buf_size * sizeof(float));

    dst = (float *)s->input->extended_data[ch];
    for (n = 0; n < s->buf_size; n++) {
        dst[n] *= s->window_func_lut[n] * level_in;
    }

    av_rdft_calc(s->rdft[ch], (float *)s->input->extended_data[ch]);

    return 0;
}