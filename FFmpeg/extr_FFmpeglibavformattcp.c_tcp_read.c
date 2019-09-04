#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  rw_timeout; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ TCPContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVIO_FLAG_NONBLOCK ; 
 int ff_neterrno () ; 
 int ff_network_wait_fd_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_read(URLContext *h, uint8_t *buf, int size)
{
    TCPContext *s = h->priv_data;
    int ret;

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd_timeout(s->fd, 0, h->rw_timeout, &h->interrupt_callback);
        if (ret)
            return ret;
    }
    ret = recv(s->fd, buf, size, 0);
    if (ret == 0)
        return AVERROR_EOF;
    return ret < 0 ? ff_neterrno() : ret;
}