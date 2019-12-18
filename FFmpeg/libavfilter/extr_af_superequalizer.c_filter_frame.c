#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__** outputs; TYPE_2__* priv; } ;
struct TYPE_16__ {TYPE_5__* dst; } ;
struct TYPE_15__ {int channels; int nb_samples; int /*<<< orphan*/  pts; scalar_t__* extended_data; } ;
struct TYPE_14__ {float* ires; float* fsamples; int winlen; int tabsize; int /*<<< orphan*/  irdft; int /*<<< orphan*/  rdft; TYPE_1__* out; } ;
struct TYPE_13__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ SuperEqualizerContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,float*) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_audio_buffer (TYPE_4__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    SuperEqualizerContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    const float *ires = s->ires;
    float *fsamples = s->fsamples;
    int ch, i;

    AVFrame *out = ff_get_audio_buffer(outlink, s->winlen);
    float *src, *dst, *ptr;

    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    for (ch = 0; ch < in->channels; ch++) {
        ptr = (float *)out->extended_data[ch];
        dst = (float *)s->out->extended_data[ch];
        src = (float *)in->extended_data[ch];

        for (i = 0; i < in->nb_samples; i++)
            fsamples[i] = src[i];
        for (; i < s->tabsize; i++)
            fsamples[i] = 0;

        av_rdft_calc(s->rdft, fsamples);

        fsamples[0] = ires[0] * fsamples[0];
        fsamples[1] = ires[1] * fsamples[1];
        for (i = 1; i < s->tabsize / 2; i++) {
            float re, im;

            re = ires[i*2  ] * fsamples[i*2] - ires[i*2+1] * fsamples[i*2+1];
            im = ires[i*2+1] * fsamples[i*2] + ires[i*2  ] * fsamples[i*2+1];

            fsamples[i*2  ] = re;
            fsamples[i*2+1] = im;
        }

        av_rdft_calc(s->irdft, fsamples);

        for (i = 0; i < s->winlen; i++)
            dst[i] += fsamples[i] / s->tabsize * 2;
        for (i = s->winlen; i < s->tabsize; i++)
            dst[i]  = fsamples[i] / s->tabsize * 2;
        for (i = 0; i < s->winlen; i++)
            ptr[i] = dst[i];
        for (i = 0; i < s->winlen; i++)
            dst[i] = dst[i+s->winlen];
    }

    out->pts = in->pts;
    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}