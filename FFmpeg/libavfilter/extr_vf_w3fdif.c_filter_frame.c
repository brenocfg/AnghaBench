#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* prev; TYPE_2__* cur; scalar_t__ deint; TYPE_2__* next; } ;
typedef  TYPE_1__ W3FDIFContext ;
struct TYPE_14__ {int /*<<< orphan*/ * outputs; scalar_t__ is_disabled; TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_4__* dst; } ;
struct TYPE_12__ {int pts; int /*<<< orphan*/  interlaced_frame; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int filter (TYPE_4__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    W3FDIFContext *s = ctx->priv;
    int ret;

    av_frame_free(&s->prev);
    s->prev = s->cur;
    s->cur  = s->next;
    s->next = frame;

    if (!s->cur) {
        s->cur = av_frame_clone(s->next);
        if (!s->cur)
            return AVERROR(ENOMEM);
    }

    if ((s->deint && !s->cur->interlaced_frame) || ctx->is_disabled) {
        AVFrame *out = av_frame_clone(s->cur);
        if (!out)
            return AVERROR(ENOMEM);

        av_frame_free(&s->prev);
        if (out->pts != AV_NOPTS_VALUE)
            out->pts *= 2;
        return ff_filter_frame(ctx->outputs[0], out);
    }

    if (!s->prev)
        return 0;

    ret = filter(ctx, 0);
    if (ret < 0)
        return ret;

    return filter(ctx, 1);
}