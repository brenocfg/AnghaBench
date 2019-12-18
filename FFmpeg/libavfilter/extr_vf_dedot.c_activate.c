#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {int plane; int /*<<< orphan*/  pts; struct TYPE_21__* out; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_23__ {TYPE_1__* internal; int /*<<< orphan*/  is_disabled; TYPE_3__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_22__ {int eof; int eof_frames; int m; TYPE_2__** frames; int /*<<< orphan*/ * planeheight; int /*<<< orphan*/  derainbow; int /*<<< orphan*/  dedotcrawl; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* execute ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DedotContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int av_frame_make_writable (TYPE_2__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_5__*,int) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    DedotContext *s = ctx->priv;
    AVFrame *frame = NULL;
    int64_t pts;
    int status;
    int ret = 0;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (s->eof == 0) {
        ret = ff_inlink_consume_frame(inlink, &frame);
        if (ret < 0)
            return ret;
    }
    if (frame || s->eof_frames > 0) {
        AVFrame *out = NULL;

        if (frame) {
            for (int i = 2; i < 5; i++) {
                if (!s->frames[i])
                    s->frames[i] = av_frame_clone(frame);
            }
            av_frame_free(&frame);
        } else if (s->frames[3]) {
            s->eof_frames--;
            s->frames[4] = av_frame_clone(s->frames[3]);
        }

        if (s->frames[0] &&
            s->frames[1] &&
            s->frames[2] &&
            s->frames[3] &&
            s->frames[4]) {
            out = av_frame_clone(s->frames[2]);
            if (out && !ctx->is_disabled) {
                ret = av_frame_make_writable(out);
                if (ret >= 0) {
                    if (s->m & 1)
                        ctx->internal->execute(ctx, s->dedotcrawl, out, NULL,
                                               FFMIN(s->planeheight[0],
                                               ff_filter_get_nb_threads(ctx)));
                    if (s->m & 2) {
                        ThreadData td;
                        td.out = out; td.plane = 1;
                        ctx->internal->execute(ctx, s->derainbow, &td, NULL,
                                               FFMIN(s->planeheight[1],
                                               ff_filter_get_nb_threads(ctx)));
                        td.plane = 2;
                        ctx->internal->execute(ctx, s->derainbow, &td, NULL,
                                               FFMIN(s->planeheight[2],
                                               ff_filter_get_nb_threads(ctx)));
                    }
                }
            } else if (!out) {
                ret = AVERROR(ENOMEM);
            }
        }

        av_frame_free(&s->frames[0]);
        s->frames[0] = s->frames[1];
        s->frames[1] = s->frames[2];
        s->frames[2] = s->frames[3];
        s->frames[3] = s->frames[4];
        s->frames[4] = NULL;

        if (ret < 0)
            return ret;
        if (out)
            return ff_filter_frame(outlink, out);
    }

    if (s->eof) {
        if (s->eof_frames <= 0) {
            ff_outlink_set_status(outlink, AVERROR_EOF, s->frames[2]->pts);
        } else {
            ff_filter_set_ready(ctx, 10);
        }
        return 0;
    }

    if (!s->eof && ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        if (status == AVERROR_EOF) {
            s->eof = 1;
            s->eof_frames = !!s->frames[0] + !!s->frames[1];
            if (s->eof_frames <= 0) {
                ff_outlink_set_status(outlink, AVERROR_EOF, pts);
                return 0;
            }
            ff_filter_set_ready(ctx, 10);
            return 0;
        }
    }

    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}