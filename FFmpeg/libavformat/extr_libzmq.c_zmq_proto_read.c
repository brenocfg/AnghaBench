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
struct TYPE_6__ {int /*<<< orphan*/  pkt_size_overflow; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ ZMQContext ;
struct TYPE_7__ {int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  rw_timeout; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ URLContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZMQ_STRERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zmq_proto_wait_timeout (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zmq_recv (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zmq_proto_read(URLContext *h, unsigned char *buf, int size)
{
    int ret;
    ZMQContext *s = h->priv_data;

    ret = zmq_proto_wait_timeout(h, s->socket, 0, h->rw_timeout, &h->interrupt_callback);
    if (ret)
        return ret;
    ret = zmq_recv(s->socket, buf, size, 0);
    if (ret == -1) {
        av_log(h, AV_LOG_ERROR, "Error occured during zmq_recv(): %s\n", ZMQ_STRERROR);
        return AVERROR_EXTERNAL;
    }
    if (ret > size) {
        s->pkt_size_overflow = FFMAX(s->pkt_size_overflow, ret);
        av_log(h, AV_LOG_WARNING, "Message exceeds available space in the buffer. Message will be truncated. Setting -pkt_size %d may resolve the issue.\n", s->pkt_size_overflow);
        ret = size;
    }
    return ret; /*number of bytes read*/
}