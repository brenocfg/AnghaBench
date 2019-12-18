#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* src; } ;
struct TYPE_5__ {scalar_t__ available; int eof; int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ DeflickerContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_bufqueue_peek (int /*<<< orphan*/ *,scalar_t__) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    DeflickerContext *s = ctx->priv;
    int ret;

    ret = ff_request_frame(ctx->inputs[0]);
    if (ret == AVERROR_EOF && s->available > 0) {
        AVFrame *buf = ff_bufqueue_peek(&s->q, s->available - 1);
        if (!buf)
            return AVERROR(ENOMEM);
        buf = av_frame_clone(buf);
        if (!buf)
            return AVERROR(ENOMEM);

        s->eof = 1;
        ret = filter_frame(ctx->inputs[0], buf);
        s->available--;
    }

    return ret;
}