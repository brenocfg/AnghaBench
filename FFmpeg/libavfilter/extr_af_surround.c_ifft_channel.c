#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {scalar_t__* extended_data; } ;
struct TYPE_9__ {float* output_levels; int hop_size; int buf_size; float* window_func_lut; TYPE_2__* overlap_buffer; TYPE_1__* output; int /*<<< orphan*/ * irdft; } ;
struct TYPE_8__ {scalar_t__* extended_data; } ;
struct TYPE_7__ {scalar_t__* extended_data; } ;
typedef  TYPE_3__ AudioSurroundContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ifft_channel(AVFilterContext *ctx, void *arg, int ch, int nb_jobs)
{
    AudioSurroundContext *s = ctx->priv;
    const float level_out = s->output_levels[ch];
    AVFrame *out = arg;
    float *dst, *ptr;
    int n;

    av_rdft_calc(s->irdft[ch], (float *)s->output->extended_data[ch]);

    dst = (float *)s->output->extended_data[ch];
    ptr = (float *)s->overlap_buffer->extended_data[ch];

    memmove(s->overlap_buffer->extended_data[ch],
            s->overlap_buffer->extended_data[ch] + s->hop_size * sizeof(float),
            s->buf_size * sizeof(float));
    memset(s->overlap_buffer->extended_data[ch] + s->buf_size * sizeof(float),
           0, s->hop_size * sizeof(float));

    for (n = 0; n < s->buf_size; n++) {
        ptr[n] += dst[n] * s->window_func_lut[n] * level_out;
    }

    ptr = (float *)s->overlap_buffer->extended_data[ch];
    dst = (float *)out->extended_data[ch];
    memcpy(dst, ptr, s->hop_size * sizeof(float));

    return 0;
}