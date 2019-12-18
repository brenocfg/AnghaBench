#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {unsigned int nb_outputs; unsigned int nb_inputs; int /*<<< orphan*/ * inputs; int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
struct TYPE_10__ {unsigned int cur_idx; TYPE_1__* in; int /*<<< orphan*/  nb_in_active; } ;
struct TYPE_9__ {int eof; } ;
typedef  TYPE_2__ ConcatContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  close_input (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_3__*,int) ; 
 int ff_inlink_acknowledge_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_inlink_set_status (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ ) ; 
 int ff_outlink_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int flush_segment (TYPE_3__*) ; 
 int push_frame (TYPE_3__*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    ConcatContext *cat = ctx->priv;
    AVFrame *frame;
    unsigned i, j;
    int ret, status;
    int64_t pts;

    /* Forward status back */
    for (i = 0; i < ctx->nb_outputs; i++) {
        status = ff_outlink_get_status(ctx->outputs[i]);
        if (!status)
            continue;
        for (j = i; j < ctx->nb_inputs; j += ctx->nb_outputs) {
            if (!cat->in[j].eof) {
                cat->in[j].eof = 1;
                ff_inlink_set_status(ctx->inputs[j], status);
                return 0;
            }
        }

    }

    /* Forward available frames */
    if (cat->cur_idx < ctx->nb_inputs) {
        for (i = 0; i < ctx->nb_outputs; i++) {
            ret = ff_inlink_consume_frame(ctx->inputs[cat->cur_idx + i], &frame);
            if (ret < 0)
                return ret;
            if (ret) {
                ff_filter_set_ready(ctx, 10);
                return push_frame(ctx, cat->cur_idx + i, frame);
            }
        }
    }

    /* Forward status change */
    if (cat->cur_idx < ctx->nb_inputs) {
        for (i = 0; i < ctx->nb_outputs; i++) {
            ret = ff_inlink_acknowledge_status(ctx->inputs[cat->cur_idx + i], &status, &pts);
            /* TODO use pts */
            if (ret > 0) {
                close_input(ctx, cat->cur_idx + i);
                if (cat->cur_idx + ctx->nb_outputs >= ctx->nb_inputs) {
                    ff_outlink_set_status(ctx->outputs[i], status, pts);
                }
                if (!cat->nb_in_active) {
                    ret = flush_segment(ctx);
                    if (ret < 0)
                        return ret;
                }
                ff_filter_set_ready(ctx, 10);
                return 0;
            }
        }
    }

    ret = FFERROR_NOT_READY;
    for (i = 0; i < ctx->nb_outputs; i++) {
        if (ff_outlink_frame_wanted(ctx->outputs[i])) {
            if (cat->in[cat->cur_idx + i].eof) {
                for (j = 0; j < ctx->nb_outputs; j++)
                    if (!cat->in[cat->cur_idx + j].eof)
                        ff_inlink_request_frame(ctx->inputs[cat->cur_idx + j]);
                return 0;
            } else {
                ff_inlink_request_frame(ctx->inputs[cat->cur_idx + i]);
                ret = 0;
            }
        }
    }

    return ret;
}