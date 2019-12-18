#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; int /*<<< orphan*/  pkt; } ;
struct TYPE_8__ {int /*<<< orphan*/  header_written; } ;
typedef  TYPE_1__ FifoThreadContext ;
typedef  TYPE_2__ FifoMessage ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
#define  FIFO_FLUSH_OUTPUT 130 
#define  FIFO_WRITE_HEADER 129 
#define  FIFO_WRITE_PACKET 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int fifo_thread_flush_output (TYPE_1__*) ; 
 int fifo_thread_write_header (TYPE_1__*) ; 
 int fifo_thread_write_packet (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fifo_thread_dispatch_message(FifoThreadContext *ctx, FifoMessage *msg)
{
    int ret = AVERROR(EINVAL);

    if (!ctx->header_written) {
        ret = fifo_thread_write_header(ctx);
        if (ret < 0)
            return ret;
    }

    switch(msg->type) {
    case FIFO_WRITE_HEADER:
        av_assert0(ret >= 0);
        return ret;
    case FIFO_WRITE_PACKET:
        return fifo_thread_write_packet(ctx, &msg->pkt);
    case FIFO_FLUSH_OUTPUT:
        return fifo_thread_flush_output(ctx);
    }

    av_assert0(0);
    return AVERROR(EINVAL);
}