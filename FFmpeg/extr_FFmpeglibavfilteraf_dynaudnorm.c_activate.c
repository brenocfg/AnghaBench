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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_5__ {int eof; scalar_t__ frame_len; scalar_t__ delay; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_2__*,int) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ ff_inlink_queued_samples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    DynamicAudioNormalizerContext *s = ctx->priv;
    AVFrame *in = NULL;
    int ret = 0, status;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (!s->eof) {
        ret = ff_inlink_consume_samples(inlink, s->frame_len, s->frame_len, &in);
        if (ret < 0)
            return ret;
        if (ret > 0) {
            ret = filter_frame(inlink, in);
            if (ret <= 0)
                return ret;
        }

        if (ff_inlink_queued_samples(inlink) >= s->frame_len) {
            ff_filter_set_ready(ctx, 10);
            return 0;
        }
    }

    if (!s->eof && ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        if (status == AVERROR_EOF)
            s->eof = 1;
    }

    if (s->eof && s->delay > 0)
        return flush(outlink);

    if (s->eof && s->delay <= 0) {
        ff_outlink_set_status(outlink, AVERROR_EOF, s->pts);
        return 0;
    }

    if (!s->eof)
        FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}