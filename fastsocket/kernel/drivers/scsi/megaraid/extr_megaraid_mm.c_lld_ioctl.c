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
struct TYPE_6__ {int status; scalar_t__ timedout; } ;
typedef  TYPE_1__ uioc_t ;
struct timer_list {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_7__ {int (* issue_uioc ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ;int timeout; scalar_t__ quiescent; int /*<<< orphan*/  drvr_data; } ;
typedef  TYPE_2__ mraid_mmadp_t ;

/* Variables and functions */
 int ENODATA ; 
 int HZ ; 
 int /*<<< orphan*/  IOCTL_ISSUE ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  init_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lld_timedout ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_q ; 

__attribute__((used)) static int
lld_ioctl(mraid_mmadp_t *adp, uioc_t *kioc)
{
	int			rval;
	struct timer_list	timer;
	struct timer_list	*tp = NULL;

	kioc->status	= -ENODATA;
	rval		= adp->issue_uioc(adp->drvr_data, kioc, IOCTL_ISSUE);

	if (rval) return rval;

	/*
	 * Start the timer
	 */
	if (adp->timeout > 0) {
		tp		= &timer;
		init_timer(tp);

		tp->function	= lld_timedout;
		tp->data	= (unsigned long)kioc;
		tp->expires	= jiffies + adp->timeout * HZ;

		add_timer(tp);
	}

	/*
	 * Wait till the low level driver completes the ioctl. After this
	 * call, the ioctl either completed successfully or timedout.
	 */
	wait_event(wait_q, (kioc->status != -ENODATA));
	if (tp) {
		del_timer_sync(tp);
	}

	/*
	 * If the command had timedout, we mark the controller offline
	 * before returning
	 */
	if (kioc->timedout) {
		adp->quiescent = 0;
	}

	return kioc->status;
}