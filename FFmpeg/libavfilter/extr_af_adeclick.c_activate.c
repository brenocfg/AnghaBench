#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {TYPE_1__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_9__ {scalar_t__ pts; int /*<<< orphan*/  nb_samples; scalar_t__ extended_data; } ;
struct TYPE_8__ {scalar_t__ window_size; scalar_t__ pts; scalar_t__ samples_left; int eof; scalar_t__ overlap_skip; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ AudioDeclickContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int av_audio_fifo_write (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_3__*,int) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int filter_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AudioDeclickContext *s = ctx->priv;
    AVFrame *in;
    int ret, status;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    ret = ff_inlink_consume_samples(inlink, s->window_size, s->window_size, &in);
    if (ret < 0)
        return ret;
    if (ret > 0) {
        if (s->pts == AV_NOPTS_VALUE)
            s->pts = in->pts;

        ret = av_audio_fifo_write(s->fifo, (void **)in->extended_data,
                                  in->nb_samples);
        av_frame_free(&in);
        if (ret < 0)
            return ret;
    }

    if (av_audio_fifo_size(s->fifo) >= s->window_size ||
        s->samples_left > 0)
        return filter_frame(inlink);

    if (av_audio_fifo_size(s->fifo) >= s->window_size) {
        ff_filter_set_ready(ctx, 100);
        return 0;
    }

    if (!s->eof && ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        if (status == AVERROR_EOF) {
            s->eof = 1;
            s->samples_left = av_audio_fifo_size(s->fifo) - s->overlap_skip;
            ff_filter_set_ready(ctx, 100);
            return 0;
        }
    }

    if (s->eof && s->samples_left <= 0) {
        ff_outlink_set_status(outlink, AVERROR_EOF, s->pts);
        return 0;
    }

    if (!s->eof)
        FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}