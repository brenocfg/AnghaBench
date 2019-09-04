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
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ UnixContext ;
struct TYPE_5__ {int flags; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ URLContext ;

/* Variables and functions */
 int AVIO_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int ff_neterrno () ; 
 int ff_network_wait_fd (int /*<<< orphan*/ ,int) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unix_write(URLContext *h, const uint8_t *buf, int size)
{
    UnixContext *s = h->priv_data;
    int ret;

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd(s->fd, 1);
        if (ret < 0)
            return ret;
    }
    ret = send(s->fd, buf, size, MSG_NOSIGNAL);
    return ret < 0 ? ff_neterrno() : ret;
}