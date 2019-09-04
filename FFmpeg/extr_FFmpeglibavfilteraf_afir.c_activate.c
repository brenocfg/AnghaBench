#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_25__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_24__ {TYPE_7__** inputs; TYPE_2__** outputs; TYPE_1__* priv; } ;
struct TYPE_23__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_22__ {int eof_coeffs; int min_part_size; scalar_t__ response; TYPE_17__* video; int /*<<< orphan*/  pts; scalar_t__ have_coeffs; } ;
struct TYPE_21__ {scalar_t__ pts; } ;
typedef  TYPE_1__ AudioFIRContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFERROR_NOT_READY ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_clone (TYPE_17__*) ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_ir (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int convert_coeffs (TYPE_3__*) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_3__*,int) ; 
 scalar_t__ ff_inlink_acknowledge_status (TYPE_7__*,int*,scalar_t__*) ; 
 int ff_inlink_consume_samples (TYPE_7__*,int,int,int /*<<< orphan*/ **) ; 
 int ff_inlink_queued_samples (TYPE_7__*) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (TYPE_7__*) ; 
 scalar_t__ ff_outlink_frame_wanted (TYPE_2__*) ; 
 int ff_outlink_get_status (TYPE_7__*) ; 
 int /*<<< orphan*/  ff_outlink_set_status (TYPE_2__*,int,scalar_t__) ; 
 int fir_frame (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AudioFIRContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int ret, status, available, wanted;
    AVFrame *in = NULL;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(ctx->outputs[0], ctx);
    if (s->response)
        FF_FILTER_FORWARD_STATUS_BACK_ALL(ctx->outputs[1], ctx);
    if (!s->eof_coeffs) {
        AVFrame *ir = NULL;

        ret = check_ir(ctx->inputs[1], ir);
        if (ret < 0)
            return ret;

        if (ff_outlink_get_status(ctx->inputs[1]) == AVERROR_EOF)
            s->eof_coeffs = 1;

        if (!s->eof_coeffs) {
            if (ff_outlink_frame_wanted(ctx->outputs[0]))
                ff_inlink_request_frame(ctx->inputs[1]);
            else if (s->response && ff_outlink_frame_wanted(ctx->outputs[1]))
                ff_inlink_request_frame(ctx->inputs[1]);
            return 0;
        }
    }

    if (!s->have_coeffs && s->eof_coeffs) {
        ret = convert_coeffs(ctx);
        if (ret < 0)
            return ret;
    }

    available = ff_inlink_queued_samples(ctx->inputs[0]);
    wanted = FFMAX(s->min_part_size, (available / s->min_part_size) * s->min_part_size);
    ret = ff_inlink_consume_samples(ctx->inputs[0], wanted, wanted, &in);
    if (ret > 0)
        ret = fir_frame(s, in, outlink);

    if (ret < 0)
        return ret;

    if (s->response && s->have_coeffs) {
        int64_t old_pts = s->video->pts;
        int64_t new_pts = av_rescale_q(s->pts, ctx->inputs[0]->time_base, ctx->outputs[1]->time_base);

        if (ff_outlink_frame_wanted(ctx->outputs[1]) && old_pts < new_pts) {
            s->video->pts = new_pts;
            return ff_filter_frame(ctx->outputs[1], av_frame_clone(s->video));
        }
    }

    if (ff_inlink_queued_samples(ctx->inputs[0]) >= s->min_part_size) {
        ff_filter_set_ready(ctx, 10);
        return 0;
    }

    if (ff_inlink_acknowledge_status(ctx->inputs[0], &status, &pts)) {
        if (status == AVERROR_EOF) {
            ff_outlink_set_status(ctx->outputs[0], status, pts);
            if (s->response)
                ff_outlink_set_status(ctx->outputs[1], status, pts);
            return 0;
        }
    }

    if (ff_outlink_frame_wanted(ctx->outputs[0]) &&
        !ff_outlink_get_status(ctx->inputs[0])) {
        ff_inlink_request_frame(ctx->inputs[0]);
        return 0;
    }

    if (s->response &&
        ff_outlink_frame_wanted(ctx->outputs[1]) &&
        !ff_outlink_get_status(ctx->inputs[0])) {
        ff_inlink_request_frame(ctx->inputs[0]);
        return 0;
    }

    return FFERROR_NOT_READY;
}