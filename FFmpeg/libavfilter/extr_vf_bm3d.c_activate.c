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
struct TYPE_6__ {int /*<<< orphan*/ * inputs; int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ BM3DContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_framesync_activate (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int filter_frame (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    BM3DContext *s = ctx->priv;

    if (!s->ref) {
        AVFrame *frame = NULL;
        AVFrame *out = NULL;
        int ret, status;
        int64_t pts;

        FF_FILTER_FORWARD_STATUS_BACK(ctx->outputs[0], ctx->inputs[0]);

        if ((ret = ff_inlink_consume_frame(ctx->inputs[0], &frame)) > 0) {
            ret = filter_frame(ctx, &out, frame, frame);
            av_frame_free(&frame);
            if (ret < 0)
                return ret;
            ret = ff_filter_frame(ctx->outputs[0], out);
        }
        if (ret < 0) {
            return ret;
        } else if (ff_inlink_acknowledge_status(ctx->inputs[0], &status, &pts)) {
            ff_outlink_set_status(ctx->outputs[0], status, pts);
            return 0;
        } else {
            if (ff_outlink_frame_wanted(ctx->outputs[0]))
                ff_inlink_request_frame(ctx->inputs[0]);
            return 0;
        }
    } else {
        return ff_framesync_activate(&s->fs);
    }
}