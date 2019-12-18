#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_5__* out; TYPE_5__* in; } ;
typedef  TYPE_3__ ThreadData ;
struct TYPE_28__ {TYPE_1__* internal; TYPE_6__** outputs; TYPE_4__* priv; } ;
struct TYPE_27__ {int channels; TYPE_7__* dst; } ;
struct TYPE_26__ {int /*<<< orphan*/  nb_samples; } ;
struct TYPE_25__ {TYPE_2__* cache; } ;
struct TYPE_23__ {scalar_t__ clippings; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ BiquadsContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_7__*) ; 
 TYPE_5__* ff_get_audio_buffer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_channel ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *buf)
{
    AVFilterContext  *ctx = inlink->dst;
    BiquadsContext *s     = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out_buf;
    ThreadData td;
    int ch;

    if (av_frame_is_writable(buf)) {
        out_buf = buf;
    } else {
        out_buf = ff_get_audio_buffer(outlink, buf->nb_samples);
        if (!out_buf) {
            av_frame_free(&buf);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out_buf, buf);
    }

    td.in = buf;
    td.out = out_buf;
    ctx->internal->execute(ctx, filter_channel, &td, NULL, FFMIN(outlink->channels, ff_filter_get_nb_threads(ctx)));

    for (ch = 0; ch < outlink->channels; ch++) {
        if (s->cache[ch].clippings > 0)
            av_log(ctx, AV_LOG_WARNING, "Channel %d clipping %d times. Please reduce gain.\n",
                   ch, s->cache[ch].clippings);
        s->cache[ch].clippings = 0;
    }

    if (buf != out_buf)
        av_frame_free(&buf);

    return ff_filter_frame(outlink, out_buf);
}