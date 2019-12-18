#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zmq_msg_t ;
struct TYPE_5__ {int /*<<< orphan*/  responder; } ;
typedef  TYPE_1__ ZMQContext ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ZMQ_DONTWAIT ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* av_malloc (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmq_msg_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_msg_data (int /*<<< orphan*/ *) ; 
 int zmq_msg_init (int /*<<< orphan*/ *) ; 
 int zmq_msg_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zmq_msg_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_strerror (scalar_t__) ; 

__attribute__((used)) static int recv_msg(AVFilterContext *ctx, char **buf, int *buf_size)
{
    ZMQContext *zmq = ctx->priv;
    zmq_msg_t msg;
    int ret = 0;

    if (zmq_msg_init(&msg) == -1) {
        av_log(ctx, AV_LOG_WARNING,
               "Could not initialize receive message: %s\n", zmq_strerror(errno));
        return AVERROR_EXTERNAL;
    }

    if (zmq_msg_recv(&msg, zmq->responder, ZMQ_DONTWAIT) == -1) {
        if (errno != EAGAIN)
            av_log(ctx, AV_LOG_WARNING,
                   "Could not receive message: %s\n", zmq_strerror(errno));
        ret = AVERROR_EXTERNAL;
        goto end;
    }

    *buf_size = zmq_msg_size(&msg) + 1;
    *buf = av_malloc(*buf_size);
    if (!*buf) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    memcpy(*buf, zmq_msg_data(&msg), *buf_size - 1);
    (*buf)[*buf_size-1] = 0;

end:
    zmq_msg_close(&msg);
    return ret;
}