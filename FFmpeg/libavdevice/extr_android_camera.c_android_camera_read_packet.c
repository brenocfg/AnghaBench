#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_7__ {int /*<<< orphan*/  input_queue; int /*<<< orphan*/  exit; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVFMT_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  AV_THREAD_MESSAGE_NONBLOCK ; 
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 
 int av_thread_message_queue_recv (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int android_camera_read_packet(AVFormatContext *avctx, AVPacket *pkt)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    int ret;

    if (!atomic_load(&ctx->exit)) {
        ret = av_thread_message_queue_recv(ctx->input_queue, pkt,
                avctx->flags & AVFMT_FLAG_NONBLOCK ? AV_THREAD_MESSAGE_NONBLOCK : 0);
    } else {
        ret = AVERROR_EOF;
    }

    if (ret < 0) {
        return ret;
    } else {
        return pkt->size;
    }
}