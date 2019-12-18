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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  rw_timeout; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  eid; } ;
typedef  TYPE_2__ SRTContext ;

/* Variables and functions */
 int AVIO_FLAG_NONBLOCK ; 
 int libsrt_neterrno (TYPE_1__*) ; 
 int libsrt_network_wait_fd_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srt_recvmsg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int libsrt_read(URLContext *h, uint8_t *buf, int size)
{
    SRTContext *s = h->priv_data;
    int ret;

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = libsrt_network_wait_fd_timeout(h, s->eid, s->fd, 0, h->rw_timeout, &h->interrupt_callback);
        if (ret)
            return ret;
    }

    ret = srt_recvmsg(s->fd, buf, size);
    if (ret < 0) {
        ret = libsrt_neterrno(h);
    }

    return ret;
}