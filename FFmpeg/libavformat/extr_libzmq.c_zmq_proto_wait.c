#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* socket; int events; int revents; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ zmq_pollitem_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  POLLING_TIME ; 
 int ZMQ_POLLIN ; 
 int ZMQ_POLLOUT ; 
 int /*<<< orphan*/  ZMQ_STRERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zmq_poll (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zmq_proto_wait(URLContext *h, void *socket, int write)
{
    int ret;
    int ev = write ? ZMQ_POLLOUT : ZMQ_POLLIN;
    zmq_pollitem_t items = { .socket = socket, .fd = 0, .events = ev, .revents = 0 };
    ret = zmq_poll(&items, 1, POLLING_TIME);
    if (ret == -1) {
        av_log(h, AV_LOG_ERROR, "Error occured during zmq_poll(): %s\n", ZMQ_STRERROR);
        return AVERROR_EXTERNAL;
    }
    return items.revents & ev ? 0 : AVERROR(EAGAIN);
}