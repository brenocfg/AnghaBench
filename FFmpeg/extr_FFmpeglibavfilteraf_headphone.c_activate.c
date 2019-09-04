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
struct TYPE_10__ {int /*<<< orphan*/ ** inputs; int /*<<< orphan*/ ** outputs; TYPE_2__* priv; } ;
struct TYPE_9__ {int eof_hrirs; int nb_inputs; int /*<<< orphan*/  size; int /*<<< orphan*/  have_hrirs; TYPE_1__* in; } ;
struct TYPE_8__ {int eof; } ;
typedef  TYPE_2__ HeadphoneContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVERROR_EOF ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int check_ir (int /*<<< orphan*/ *,int) ; 
 int convert_coeffs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_outlink_get_status (int /*<<< orphan*/ *) ; 
 int headphone_frame (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    HeadphoneContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *in = NULL;
    int i, ret;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(ctx->outputs[0], ctx);
    if (!s->eof_hrirs) {
        for (i = 1; i < s->nb_inputs; i++) {
            if (s->in[i].eof)
                continue;

            if ((ret = check_ir(ctx->inputs[i], i)) < 0)
                return ret;

            if (!s->in[i].eof) {
                if (ff_outlink_get_status(ctx->inputs[i]) == AVERROR_EOF)
                    s->in[i].eof = 1;
            }
        }

        for (i = 1; i < s->nb_inputs; i++) {
            if (!s->in[i].eof)
                break;
        }

        if (i != s->nb_inputs) {
            if (ff_outlink_frame_wanted(ctx->outputs[0])) {
                for (i = 1; i < s->nb_inputs; i++) {
                    if (!s->in[i].eof)
                        ff_inlink_request_frame(ctx->inputs[i]);
                }
            }

            return 0;
        } else {
            s->eof_hrirs = 1;
        }
    }

    if (!s->have_hrirs && s->eof_hrirs) {
        ret = convert_coeffs(ctx, inlink);
        if (ret < 0)
            return ret;
    }

    if ((ret = ff_inlink_consume_samples(ctx->inputs[0], s->size, s->size, &in)) > 0) {
        ret = headphone_frame(s, in, outlink);
        if (ret < 0)
            return ret;
    }

    if (ret < 0)
        return ret;

    FF_FILTER_FORWARD_STATUS(ctx->inputs[0], ctx->outputs[0]);
    if (ff_outlink_frame_wanted(ctx->outputs[0]))
        ff_inlink_request_frame(ctx->inputs[0]);

    return 0;
}