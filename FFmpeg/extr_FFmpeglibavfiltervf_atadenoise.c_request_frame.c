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
struct TYPE_7__ {scalar_t__ available; int /*<<< orphan*/  q; } ;
struct TYPE_6__ {int /*<<< orphan*/ * inputs; int /*<<< orphan*/  is_disabled; TYPE_3__* priv; } ;
struct TYPE_5__ {TYPE_2__* src; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ ATADenoiseContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_peek (int /*<<< orphan*/ *,scalar_t__) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ATADenoiseContext *s = ctx->priv;
    int ret = 0;

    ret = ff_request_frame(ctx->inputs[0]);

    if (ret == AVERROR_EOF && !ctx->is_disabled && s->available) {
        AVFrame *buf = av_frame_clone(ff_bufqueue_peek(&s->q, s->available));
        if (!buf)
            return AVERROR(ENOMEM);

        ret = filter_frame(ctx->inputs[0], buf);
        s->available--;
    }

    return ret;
}