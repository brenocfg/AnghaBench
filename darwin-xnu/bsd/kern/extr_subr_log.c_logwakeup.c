#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msgbuf {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int sc_state; int sc_pgid; int /*<<< orphan*/  sc_selp; struct msgbuf* sc_mbp; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LOG_ASYNC ; 
 int /*<<< orphan*/  LOG_LOCK () ; 
 int LOG_RDWAIT ; 
 int /*<<< orphan*/  LOG_UNLOCK () ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  gsignal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_open ; 
 TYPE_1__ logsoftc ; 
 scalar_t__ oslog_is_safe () ; 
 int /*<<< orphan*/  proc_signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
logwakeup(struct msgbuf *mbp)
{
	/* cf. r24974766 & r25201228*/
	if (oslog_is_safe() == FALSE) {
		return;
	}

	LOG_LOCK();	
	if (!log_open) {
		LOG_UNLOCK();
		return;
	}
	if (NULL == mbp)
		mbp = logsoftc.sc_mbp;
	if (mbp != logsoftc.sc_mbp)
		goto out;
	selwakeup(&logsoftc.sc_selp);
	if (logsoftc.sc_state & LOG_ASYNC) {
		int pgid = logsoftc.sc_pgid;
		LOG_UNLOCK();
		if (pgid < 0)
			gsignal(-pgid, SIGIO); 
		else 
			proc_signal(pgid, SIGIO);
		LOG_LOCK();
	}
	if (logsoftc.sc_state & LOG_RDWAIT) {
		wakeup((caddr_t)mbp);
		logsoftc.sc_state &= ~LOG_RDWAIT;
	}
out:
	LOG_UNLOCK();
}