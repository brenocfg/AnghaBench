#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int nb_samples; } ;
struct TYPE_9__ {int nb_inputs; int /*<<< orphan*/ * inputs; int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_4__** input_frames; } ;
typedef  TYPE_1__ JoinContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_inlink_check_available_samples (int /*<<< orphan*/ ,int) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ ,TYPE_4__**) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ ,int,int,TYPE_4__**) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int try_push_frame (TYPE_2__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    JoinContext *s = ctx->priv;
    int i, ret, status;
    int nb_samples = 0;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(ctx->outputs[0], ctx);

    if (!s->input_frames[0]) {
        ret = ff_inlink_consume_frame(ctx->inputs[0], &s->input_frames[0]);
        if (ret < 0) {
            return ret;
        } else if (ff_inlink_acknowledge_status(ctx->inputs[0], &status, &pts)) {
            ff_outlink_set_status(ctx->outputs[0], status, pts);
            return 0;
        } else {
            if (ff_outlink_frame_wanted(ctx->outputs[0]) && !s->input_frames[0]) {
                ff_inlink_request_frame(ctx->inputs[0]);
                return 0;
            }
        }
        if (!s->input_frames[0]) {
            return 0;
        }
    }

    nb_samples = s->input_frames[0]->nb_samples;

    for (i = 1; i < ctx->nb_inputs && nb_samples > 0; i++) {
        if (s->input_frames[i])
            continue;

        if (ff_inlink_check_available_samples(ctx->inputs[i], nb_samples) > 0) {
            ret = ff_inlink_consume_samples(ctx->inputs[i], nb_samples, nb_samples, &s->input_frames[i]);
            if (ret < 0) {
                return ret;
            } else if (ff_inlink_acknowledge_status(ctx->inputs[i], &status, &pts)) {
                ff_outlink_set_status(ctx->outputs[0], status, pts);
                return 0;
            }
        } else {
            if (ff_outlink_frame_wanted(ctx->outputs[0])) {
                ff_inlink_request_frame(ctx->inputs[i]);
                return 0;
            }
        }
    }

    return try_push_frame(ctx);
}