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
struct pollfd {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  POLLIN ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ff_neterrno () ; 
 int ff_poll_interrupt (struct pollfd*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_socket_nonblock (int,int) ; 

int ff_accept(int fd, int timeout, URLContext *h)
{
    int ret;
    struct pollfd lp = { fd, POLLIN, 0 };

    ret = ff_poll_interrupt(&lp, 1, timeout, &h->interrupt_callback);
    if (ret < 0)
        return ret;

    ret = accept(fd, NULL, NULL);
    if (ret < 0)
        return ff_neterrno();
    if (ff_socket_nonblock(ret, 1) < 0)
        av_log(h, AV_LOG_DEBUG, "ff_socket_nonblock failed\n");

    return ret;
}