#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * inputs; int /*<<< orphan*/ ** outputs; TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * alpha_frame; int /*<<< orphan*/ * main_frame; } ;
typedef  TYPE_1__ AlphaMergeContext ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  draw_frame (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_outlink_get_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *outlink = ctx->outputs[0];
    AlphaMergeContext *s = ctx->priv;
    int ret;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(outlink, ctx);

    if (!s->main_frame) {
        ret = ff_inlink_consume_frame(ctx->inputs[0], &s->main_frame);
        if (ret < 0)
            return ret;
    }

    if (!s->alpha_frame) {
        ret = ff_inlink_consume_frame(ctx->inputs[1], &s->alpha_frame);
        if (ret < 0)
            return ret;
    }

    if (s->main_frame && s->alpha_frame) {
        draw_frame(ctx, s->main_frame, s->alpha_frame);
        ret = ff_filter_frame(outlink, s->main_frame);
        av_frame_free(&s->alpha_frame);
        s->main_frame = NULL;
        return ret;
    }

    FF_FILTER_FORWARD_STATUS(ctx->inputs[0], outlink);
    FF_FILTER_FORWARD_STATUS(ctx->inputs[1], outlink);

    if (ff_outlink_frame_wanted(ctx->outputs[0]) &&
        !ff_outlink_get_status(ctx->inputs[0]) &&
        !s->main_frame) {
        ff_inlink_request_frame(ctx->inputs[0]);
        return 0;
    }

    if (ff_outlink_frame_wanted(ctx->outputs[0]) &&
        !ff_outlink_get_status(ctx->inputs[1]) &&
        !s->alpha_frame) {
        ff_inlink_request_frame(ctx->inputs[1]);
        return 0;
    }

    return FFERROR_NOT_READY;
}