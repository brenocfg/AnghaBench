#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ is_disabled; TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_15__ {TYPE_4__* dst; } ;
struct TYPE_14__ {scalar_t__ pts; scalar_t__ interlaced_frame; } ;
struct TYPE_13__ {int field; int cur_pts; TYPE_2__* dst; TYPE_2__* src; TYPE_2__* second; scalar_t__ deint; scalar_t__ eof; } ;
typedef  TYPE_1__ NNEDIContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int get_frame (TYPE_4__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *src)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    NNEDIContext *s = ctx->priv;
    int ret;

    if ((s->field > 1 ||
         s->field == -2) && !s->second) {
        goto second;
    } else if (s->field > 1 ||
               s->field == -2) {
        AVFrame *dst;

        s->src = s->second;
        ret = get_frame(ctx, 1);
        if (ret < 0) {
            av_frame_free(&s->dst);
            av_frame_free(&s->second);
            s->src = NULL;
            return ret;
        }
        dst = s->dst;

        if (src->pts != AV_NOPTS_VALUE &&
            dst->pts != AV_NOPTS_VALUE)
            dst->pts += src->pts;
        else
            dst->pts = AV_NOPTS_VALUE;

        ret = ff_filter_frame(outlink, dst);
        if (ret < 0)
            return ret;
        if (s->eof)
            return 0;
        s->cur_pts = s->second->pts;
        av_frame_free(&s->second);
second:
        if ((s->deint && src->interlaced_frame &&
             !ctx->is_disabled) ||
            (!s->deint && !ctx->is_disabled)) {
            s->second = src;
        }
    }

    if ((s->deint && !src->interlaced_frame) || ctx->is_disabled) {
        AVFrame *dst = av_frame_clone(src);
        if (!dst) {
            av_frame_free(&src);
            av_frame_free(&s->second);
            return AVERROR(ENOMEM);
        }

        if (s->field > 1 || s->field == -2) {
            av_frame_free(&s->second);
            if ((s->deint && src->interlaced_frame) ||
                (!s->deint))
                s->second = src;
        } else {
            av_frame_free(&src);
        }
        if (dst->pts != AV_NOPTS_VALUE)
            dst->pts *= 2;
        return ff_filter_frame(outlink, dst);
    }

    s->src = src;
    ret = get_frame(ctx, 0);
    if (ret < 0) {
        av_frame_free(&s->dst);
        av_frame_free(&s->src);
        av_frame_free(&s->second);
        return ret;
    }

    if (src->pts != AV_NOPTS_VALUE)
        s->dst->pts = src->pts * 2;
    if (s->field <= 1 && s->field > -2) {
        av_frame_free(&src);
        s->src = NULL;
    }

    return ff_filter_frame(outlink, s->dst);
}