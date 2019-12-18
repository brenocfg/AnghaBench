#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int eof; TYPE_1__* cur; TYPE_10__* next; int /*<<< orphan*/  current_field; scalar_t__ frame_pending; } ;
typedef  TYPE_2__ YADIFContext ;
struct TYPE_16__ {int /*<<< orphan*/ * inputs; TYPE_2__* priv; } ;
struct TYPE_15__ {TYPE_5__* src; } ;
struct TYPE_14__ {scalar_t__ pts; } ;
struct TYPE_12__ {scalar_t__ pts; } ;
struct TYPE_11__ {int pts; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  YADIF_FIELD_BACK_END ; 
 TYPE_3__* av_frame_clone (TYPE_10__*) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_yadif_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  return_frame (TYPE_5__*,int) ; 

int ff_yadif_request_frame(AVFilterLink *link)
{
    AVFilterContext *ctx = link->src;
    YADIFContext *yadif = ctx->priv;
    int ret;

    if (yadif->frame_pending) {
        return_frame(ctx, 1);
        return 0;
    }

    if (yadif->eof)
        return AVERROR_EOF;

    ret  = ff_request_frame(ctx->inputs[0]);

    if (ret == AVERROR_EOF && yadif->cur) {
        AVFrame *next = av_frame_clone(yadif->next);

        if (!next)
            return AVERROR(ENOMEM);

        yadif->current_field = YADIF_FIELD_BACK_END;
        next->pts = yadif->next->pts * 2 - yadif->cur->pts;

        ff_yadif_filter_frame(ctx->inputs[0], next);
        yadif->eof = 1;
    } else if (ret < 0) {
        return ret;
    }

    return 0;
}