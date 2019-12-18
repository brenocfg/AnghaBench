#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int draining; } ;
typedef  TYPE_1__ V4L2m2mContext ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ V4L2Context ;
typedef  int /*<<< orphan*/  V4L2Buffer ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctx_to_m2mctx (TYPE_2__*) ; 
 int ff_v4l2_buffer_avframe_to_buf (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int ff_v4l2_buffer_enqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logger (TYPE_2__*) ; 
 int /*<<< orphan*/ * v4l2_getfree_v4l2buf (TYPE_2__*) ; 
 int v4l2_stop_encode (TYPE_2__*) ; 

int ff_v4l2_context_enqueue_frame(V4L2Context* ctx, const AVFrame* frame)
{
    V4L2m2mContext *s = ctx_to_m2mctx(ctx);
    V4L2Buffer* avbuf;
    int ret;

    if (!frame) {
        ret = v4l2_stop_encode(ctx);
        if (ret)
            av_log(logger(ctx), AV_LOG_ERROR, "%s stop_encode\n", ctx->name);
        s->draining= 1;
        return 0;
    }

    avbuf = v4l2_getfree_v4l2buf(ctx);
    if (!avbuf)
        return AVERROR(ENOMEM);

    ret = ff_v4l2_buffer_avframe_to_buf(frame, avbuf);
    if (ret)
        return ret;

    return ff_v4l2_buffer_enqueue(avbuf);
}