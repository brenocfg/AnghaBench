#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int parity; scalar_t__ current_field; int frame_pending; int mode; TYPE_6__* out; TYPE_1__* next; TYPE_13__* cur; int /*<<< orphan*/  (* filter ) (TYPE_4__*,TYPE_6__*,int,int) ;} ;
typedef  TYPE_2__ YADIFContext ;
struct TYPE_19__ {scalar_t__ pts; scalar_t__ interlaced_frame; } ;
struct TYPE_18__ {TYPE_3__** outputs; TYPE_2__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_15__ {scalar_t__ pts; } ;
struct TYPE_14__ {int top_field_first; scalar_t__ pts; scalar_t__ interlaced_frame; } ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ YADIF_FIELD_BACK_END ; 
 scalar_t__ YADIF_FIELD_END ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_6__*,TYPE_13__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_6__*) ; 
 TYPE_6__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_6__*,int,int) ; 

__attribute__((used)) static int return_frame(AVFilterContext *ctx, int is_second)
{
    YADIFContext *yadif = ctx->priv;
    AVFilterLink *link  = ctx->outputs[0];
    int tff, ret;

    if (yadif->parity == -1) {
        tff = yadif->cur->interlaced_frame ?
              yadif->cur->top_field_first : 1;
    } else {
        tff = yadif->parity ^ 1;
    }

    if (is_second) {
        yadif->out = ff_get_video_buffer(link, link->w, link->h);
        if (!yadif->out)
            return AVERROR(ENOMEM);

        av_frame_copy_props(yadif->out, yadif->cur);
        yadif->out->interlaced_frame = 0;
        if (yadif->current_field == YADIF_FIELD_BACK_END)
            yadif->current_field = YADIF_FIELD_END;
    }

    yadif->filter(ctx, yadif->out, tff ^ !is_second, tff);

    if (is_second) {
        int64_t cur_pts  = yadif->cur->pts;
        int64_t next_pts = yadif->next->pts;

        if (next_pts != AV_NOPTS_VALUE && cur_pts != AV_NOPTS_VALUE) {
            yadif->out->pts = cur_pts + next_pts;
        } else {
            yadif->out->pts = AV_NOPTS_VALUE;
        }
    }
    ret = ff_filter_frame(ctx->outputs[0], yadif->out);

    yadif->frame_pending = (yadif->mode&1) && !is_second;
    return ret;
}