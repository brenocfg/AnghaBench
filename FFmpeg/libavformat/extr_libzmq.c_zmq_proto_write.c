#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ ZMQContext ;
struct TYPE_7__ {int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  rw_timeout; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ URLContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ZMQ_STRERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zmq_proto_wait_timeout (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zmq_send (int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zmq_proto_write(URLContext *h, const unsigned char *buf, int size)
{
    int ret;
    ZMQContext *s = h->priv_data;

    ret = zmq_proto_wait_timeout(h, s->socket, 1, h->rw_timeout, &h->interrupt_callback);
    if (ret)
        return ret;
    ret = zmq_send(s->socket, buf, size, 0);
    if (ret == -1) {
        av_log(h, AV_LOG_ERROR, "Error occured during zmq_send(): %s\n", ZMQ_STRERROR);
        return AVERROR_EXTERNAL;
    }
    return ret; /*number of bytes sent*/
}