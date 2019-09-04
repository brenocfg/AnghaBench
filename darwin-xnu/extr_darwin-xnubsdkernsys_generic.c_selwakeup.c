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
struct selinfo {int si_flags; int /*<<< orphan*/  si_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_EVENT64 ; 
 int SI_COLL ; 
 int SI_INITED ; 
 int SI_RECORDED ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  nselcoll ; 
 int /*<<< orphan*/  waitq_wakeup64_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
selwakeup(struct selinfo *sip)
{
	
	if ((sip->si_flags & SI_INITED) == 0) {
		return;
	}

	if (sip->si_flags & SI_COLL) {
		nselcoll++;
		sip->si_flags &= ~SI_COLL;
#if 0
		/* will not  support */
		//wakeup((caddr_t)&selwait);
#endif
	}

	if (sip->si_flags & SI_RECORDED) {
		waitq_wakeup64_all(&sip->si_waitq, NO_EVENT64,
				   THREAD_AWAKENED, WAITQ_ALL_PRIORITIES);
		sip->si_flags &= ~SI_RECORDED;
	}

}