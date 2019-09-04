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
struct waitq {int dummy; } ;
struct selinfo {int si_flags; struct waitq si_waitq; } ;

/* Variables and functions */
 int SI_CLEAR ; 
 int SI_COLL ; 
 int SI_INITED ; 
 int SI_RECORDED ; 
 int /*<<< orphan*/  selwakeup (struct selinfo*) ; 
 int /*<<< orphan*/  waitq_deinit (struct waitq*) ; 

void 
selthreadclear(struct selinfo *sip)
{
	struct waitq *wq;

	if ((sip->si_flags & SI_INITED) == 0) {
		return;
	}
	if (sip->si_flags & SI_RECORDED) {
			selwakeup(sip);
			sip->si_flags &= ~(SI_RECORDED | SI_COLL);
	}
	sip->si_flags |= SI_CLEAR;
	sip->si_flags &= ~SI_INITED;

	wq = &sip->si_waitq;

	/*
	 * Higher level logic may have a handle on this waitq's prepost ID,
	 * but that's OK because the waitq_deinit will remove/invalidate the
	 * prepost object (as well as mark the waitq invalid). This de-couples
	 * us from any callers that may have a handle to this waitq via the
	 * prepost ID.
	 */
	waitq_deinit(wq);
}