#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ done; } ;
typedef  TYPE_1__ V4L2Context ;
typedef  int /*<<< orphan*/  V4L2Buffer ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int ff_v4l2_buffer_buf_to_avpkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * v4l2_dequeue_v4l2buf (TYPE_1__*,int) ; 

int ff_v4l2_context_dequeue_packet(V4L2Context* ctx, AVPacket* pkt)
{
    V4L2Buffer* avbuf = NULL;

    /*
     * blocks until:
     *  1. encoded packet available
     *  2. an input buffer ready to be dequeued
     */
    avbuf = v4l2_dequeue_v4l2buf(ctx, -1);
    if (!avbuf) {
        if (ctx->done)
            return AVERROR_EOF;

        return AVERROR(EAGAIN);
    }

    return ff_v4l2_buffer_buf_to_avpkt(pkt, avbuf);
}