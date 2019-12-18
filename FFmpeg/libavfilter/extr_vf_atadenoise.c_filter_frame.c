#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;

/* Type definitions */
struct TYPE_30__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_28__ {int available; } ;
struct TYPE_34__ {int size; int mid; TYPE_17__ q; int /*<<< orphan*/ * planeheight; int /*<<< orphan*/  filter_slice; int /*<<< orphan*/ ** linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  available; } ;
struct TYPE_33__ {TYPE_1__* internal; int /*<<< orphan*/  is_disabled; TYPE_6__* priv; TYPE_4__** outputs; } ;
struct TYPE_32__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_31__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* execute ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;
typedef  TYPE_6__ ATADenoiseContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_frame_clone (TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_5__*,TYPE_17__*,TYPE_3__*) ; 
 TYPE_3__* ff_bufqueue_get (TYPE_17__*) ; 
 TYPE_3__* ff_bufqueue_peek (TYPE_17__*,int) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_5__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *buf)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ATADenoiseContext *s = ctx->priv;
    AVFrame *out, *in;
    int i;

    if (s->q.available != s->size) {
        if (s->q.available < s->mid) {
            for (i = 0; i < s->mid; i++) {
                out = av_frame_clone(buf);
                if (!out) {
                    av_frame_free(&buf);
                    return AVERROR(ENOMEM);
                }
                ff_bufqueue_add(ctx, &s->q, out);
            }
        }
        if (s->q.available < s->size) {
            ff_bufqueue_add(ctx, &s->q, buf);
            s->available++;
        }
        return 0;
    }

    in = ff_bufqueue_peek(&s->q, s->mid);

    if (!ctx->is_disabled) {
        ThreadData td;

        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&buf);
            return AVERROR(ENOMEM);
        }

        for (i = 0; i < s->size; i++) {
            AVFrame *frame = ff_bufqueue_peek(&s->q, i);

            s->data[0][i] = frame->data[0];
            s->data[1][i] = frame->data[1];
            s->data[2][i] = frame->data[2];
            s->linesize[0][i] = frame->linesize[0];
            s->linesize[1][i] = frame->linesize[1];
            s->linesize[2][i] = frame->linesize[2];
        }

        td.in = in; td.out = out;
        ctx->internal->execute(ctx, s->filter_slice, &td, NULL,
                               FFMIN3(s->planeheight[1],
                                      s->planeheight[2],
                                      ff_filter_get_nb_threads(ctx)));
        av_frame_copy_props(out, in);
    } else {
        out = av_frame_clone(in);
        if (!out) {
            av_frame_free(&buf);
            return AVERROR(ENOMEM);
        }
    }

    in = ff_bufqueue_get(&s->q);
    av_frame_free(&in);
    ff_bufqueue_add(ctx, &s->q, buf);

    return ff_filter_frame(outlink, out);
}