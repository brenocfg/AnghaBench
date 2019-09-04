#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  nfds_t ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int POLLING_TIME ; 
 scalar_t__ ff_check_interrupt (int /*<<< orphan*/ *) ; 
 int ff_neterrno () ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ff_poll_interrupt(struct pollfd *p, nfds_t nfds, int timeout,
                             AVIOInterruptCB *cb)
{
    int runs = timeout / POLLING_TIME;
    int ret = 0;

    do {
        if (ff_check_interrupt(cb))
            return AVERROR_EXIT;
        ret = poll(p, nfds, POLLING_TIME);
        if (ret != 0) {
            if (ret < 0)
                ret = ff_neterrno();
            if (ret == AVERROR(EINTR))
                continue;
            break;
        }
    } while (timeout <= 0 || runs-- > 0);

    if (!ret)
        return AVERROR(ETIMEDOUT);
    return ret;
}