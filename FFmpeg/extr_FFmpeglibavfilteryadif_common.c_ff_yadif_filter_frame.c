#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_10__* out; TYPE_2__* cur; TYPE_2__* prev; TYPE_2__* next; scalar_t__ deint; int /*<<< orphan*/  current_field; scalar_t__ frame_pending; } ;
typedef  TYPE_1__ YADIFContext ;
struct TYPE_25__ {int /*<<< orphan*/ * outputs; scalar_t__ is_disabled; TYPE_1__* priv; } ;
struct TYPE_24__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_23__ {scalar_t__ repeat_pict; int /*<<< orphan*/  interlaced_frame; } ;
struct TYPE_21__ {int pts; scalar_t__ interlaced_frame; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  YADIF_FIELD_END ; 
 int /*<<< orphan*/  av_assert0 (TYPE_2__*) ; 
 void* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_10__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ checkstride (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_10__*) ; 
 TYPE_10__* ff_get_video_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixstride (TYPE_3__*,TYPE_2__*) ; 
 int return_frame (TYPE_4__*,int) ; 

int ff_yadif_filter_frame(AVFilterLink *link, AVFrame *frame)
{
    AVFilterContext *ctx = link->dst;
    YADIFContext *yadif = ctx->priv;

    av_assert0(frame);

    if (yadif->frame_pending)
        return_frame(ctx, 1);

    if (yadif->prev)
        av_frame_free(&yadif->prev);
    yadif->prev = yadif->cur;
    yadif->cur  = yadif->next;
    yadif->next = frame;

    if (!yadif->cur) {
        yadif->cur = av_frame_clone(yadif->next);
        if (!yadif->cur)
            return AVERROR(ENOMEM);
        yadif->current_field = YADIF_FIELD_END;
    }

    if (checkstride(yadif, yadif->next, yadif->cur)) {
        av_log(ctx, AV_LOG_VERBOSE, "Reallocating frame due to differing stride\n");
        fixstride(link, yadif->next);
    }
    if (checkstride(yadif, yadif->next, yadif->cur))
        fixstride(link, yadif->cur);
    if (yadif->prev && checkstride(yadif, yadif->next, yadif->prev))
        fixstride(link, yadif->prev);
    if (checkstride(yadif, yadif->next, yadif->cur) || (yadif->prev && checkstride(yadif, yadif->next, yadif->prev))) {
        av_log(ctx, AV_LOG_ERROR, "Failed to reallocate frame\n");
        return -1;
    }

    if (!yadif->prev)
        return 0;

    if ((yadif->deint && !yadif->cur->interlaced_frame) ||
        ctx->is_disabled ||
        (yadif->deint && !yadif->prev->interlaced_frame && yadif->prev->repeat_pict) ||
        (yadif->deint && !yadif->next->interlaced_frame && yadif->next->repeat_pict)
    ) {
        yadif->out  = av_frame_clone(yadif->cur);
        if (!yadif->out)
            return AVERROR(ENOMEM);

        av_frame_free(&yadif->prev);
        if (yadif->out->pts != AV_NOPTS_VALUE)
            yadif->out->pts *= 2;
        return ff_filter_frame(ctx->outputs[0], yadif->out);
    }

    yadif->out = ff_get_video_buffer(ctx->outputs[0], link->w, link->h);
    if (!yadif->out)
        return AVERROR(ENOMEM);

    av_frame_copy_props(yadif->out, yadif->cur);
    yadif->out->interlaced_frame = 0;

    if (yadif->out->pts != AV_NOPTS_VALUE)
        yadif->out->pts *= 2;

    return return_frame(ctx, 0);
}