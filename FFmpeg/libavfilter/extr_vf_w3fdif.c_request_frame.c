#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int eof; TYPE_1__* cur; TYPE_9__* next; } ;
typedef  TYPE_2__ W3FDIFContext ;
struct TYPE_15__ {int pts; } ;
struct TYPE_14__ {int /*<<< orphan*/ * inputs; TYPE_2__* priv; } ;
struct TYPE_13__ {TYPE_5__* src; } ;
struct TYPE_12__ {scalar_t__ pts; } ;
struct TYPE_10__ {scalar_t__ pts; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_frame_clone (TYPE_9__*) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    W3FDIFContext *s = ctx->priv;
    int ret;

    if (s->eof)
        return AVERROR_EOF;

    ret = ff_request_frame(ctx->inputs[0]);

    if (ret == AVERROR_EOF && s->cur) {
        AVFrame *next = av_frame_clone(s->next);
        if (!next)
            return AVERROR(ENOMEM);
        next->pts = s->next->pts * 2 - s->cur->pts;
        filter_frame(ctx->inputs[0], next);
        s->eof = 1;
    } else if (ret < 0) {
        return ret;
    }

    return 0;
}