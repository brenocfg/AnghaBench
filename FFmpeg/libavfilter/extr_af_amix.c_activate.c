#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_24__ {scalar_t__ nb_frames; } ;
struct TYPE_23__ {TYPE_3__** inputs; TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_22__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_21__ {int /*<<< orphan*/  nb_samples; scalar_t__ extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int nb_inputs; int* input_state; TYPE_7__* frame_list; int /*<<< orphan*/  next_pts; int /*<<< orphan*/ * fifos; } ;
typedef  TYPE_1__ MixContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (TYPE_3__*,TYPE_4__*) ; 
 int INPUT_EOF ; 
 int INPUT_ON ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int av_audio_fifo_write (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ calc_active_inputs (TYPE_1__*) ; 
 scalar_t__ ff_inlink_acknowledge_status (TYPE_3__*,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (TYPE_3__*,TYPE_2__**) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (TYPE_3__*) ; 
 scalar_t__ ff_outlink_frame_wanted (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_outlink_set_status (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int frame_list_add_frame (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int frame_list_next_frame_size (TYPE_7__*) ; 
 int output_frame (TYPE_3__*) ; 
 int request_samples (TYPE_4__*,int) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *outlink = ctx->outputs[0];
    MixContext *s = ctx->priv;
    AVFrame *buf = NULL;
    int i, ret;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(outlink, ctx);

    for (i = 0; i < s->nb_inputs; i++) {
        AVFilterLink *inlink = ctx->inputs[i];

        if ((ret = ff_inlink_consume_frame(ctx->inputs[i], &buf)) > 0) {
            if (i == 0) {
                int64_t pts = av_rescale_q(buf->pts, inlink->time_base,
                                           outlink->time_base);
                ret = frame_list_add_frame(s->frame_list, buf->nb_samples, pts);
                if (ret < 0) {
                    av_frame_free(&buf);
                    return ret;
                }
            }

            ret = av_audio_fifo_write(s->fifos[i], (void **)buf->extended_data,
                                      buf->nb_samples);
            if (ret < 0) {
                av_frame_free(&buf);
                return ret;
            }

            av_frame_free(&buf);

            ret = output_frame(outlink);
            if (ret < 0)
                return ret;
        }
    }

    for (i = 0; i < s->nb_inputs; i++) {
        int64_t pts;
        int status;

        if (ff_inlink_acknowledge_status(ctx->inputs[i], &status, &pts)) {
            if (status == AVERROR_EOF) {
                if (i == 0) {
                    s->input_state[i] = 0;
                    if (s->nb_inputs == 1) {
                        ff_outlink_set_status(outlink, status, pts);
                        return 0;
                    }
                } else {
                    s->input_state[i] |= INPUT_EOF;
                    if (av_audio_fifo_size(s->fifos[i]) == 0) {
                        s->input_state[i] = 0;
                    }
                }
            }
        }
    }

    if (calc_active_inputs(s)) {
        ff_outlink_set_status(outlink, AVERROR_EOF, s->next_pts);
        return 0;
    }

    if (ff_outlink_frame_wanted(outlink)) {
        int wanted_samples;

        if (!(s->input_state[0] & INPUT_ON))
            return request_samples(ctx, 1);

        if (s->frame_list->nb_frames == 0) {
            ff_inlink_request_frame(ctx->inputs[0]);
            return 0;
        }
        av_assert0(s->frame_list->nb_frames > 0);

        wanted_samples = frame_list_next_frame_size(s->frame_list);

        return request_samples(ctx, wanted_samples);
    }

    return 0;
}