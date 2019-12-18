#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_20__ {int /*<<< orphan*/  channels; TYPE_6__* dst; } ;
struct TYPE_19__ {scalar_t__ pts; scalar_t__ nb_samples; scalar_t__ extended_data; } ;
struct TYPE_18__ {scalar_t__ pts; scalar_t__ offset; int H; int N; scalar_t__ eof_left; int /*<<< orphan*/  fifo; TYPE_1__* in; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {scalar_t__ extended_data; } ;
typedef  TYPE_3__ AudioNLMeansContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FFMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  av_audio_fifo_drain (int /*<<< orphan*/ ,int) ; 
 int av_audio_fifo_peek (int /*<<< orphan*/ ,void**,int) ; 
 int av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int av_audio_fifo_write (int /*<<< orphan*/ ,void**,scalar_t__) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_audio_buffer (TYPE_5__*,int) ; 
 int /*<<< orphan*/  filter_channel ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AudioNLMeansContext *s = ctx->priv;
    AVFrame *out = NULL;
    int available, wanted, ret;

    if (s->pts == AV_NOPTS_VALUE)
        s->pts = in->pts;

    ret = av_audio_fifo_write(s->fifo, (void **)in->extended_data,
                              in->nb_samples);
    av_frame_free(&in);

    s->offset = 0;
    available = av_audio_fifo_size(s->fifo);
    wanted = (available / s->H) * s->H;

    if (wanted >= s->H && available >= s->N) {
        out = ff_get_audio_buffer(outlink, wanted);
        if (!out)
            return AVERROR(ENOMEM);
    }

    while (available >= s->N) {
        ret = av_audio_fifo_peek(s->fifo, (void **)s->in->extended_data, s->N);
        if (ret < 0)
            break;

        ctx->internal->execute(ctx, filter_channel, out, NULL, inlink->channels);

        av_audio_fifo_drain(s->fifo, s->H);

        s->offset += s->H;
        available -= s->H;
    }

    if (out) {
        out->pts = s->pts;
        out->nb_samples = s->offset;
        if (s->eof_left >= 0) {
            out->nb_samples = FFMIN(s->eof_left, s->offset);
            s->eof_left -= out->nb_samples;
        }
        s->pts += s->offset;

        return ff_filter_frame(outlink, out);
    }

    return ret;
}