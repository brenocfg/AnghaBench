#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {scalar_t__ t_state; int t_rxtshift; int t_softerror; } ;
struct rtentry {int dummy; } ;
struct TYPE_5__ {struct rtentry* ro_rt; } ;
struct inpcb {scalar_t__ inp_state; TYPE_1__ inp_route; scalar_t__ inp_ppcb; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  so_timeo; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 TYPE_2__* so ; 
 int /*<<< orphan*/  sorwakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  sowwakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  tcp_drop (struct tcpcb*,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_notify(struct inpcb *inp, int error)
{
	struct tcpcb *tp;

	if (inp == NULL || (inp->inp_state == INPCB_STATE_DEAD))
		return; /* pcb is gone already */

	tp = (struct tcpcb *)inp->inp_ppcb;

	VERIFY(tp != NULL);
	/*
	 * Ignore some errors if we are hooked up.
	 * If connection hasn't completed, has retransmitted several times,
	 * and receives a second error, give up now.  This is better
	 * than waiting a long time to establish a connection that
	 * can never complete.
	 */
	if (tp->t_state == TCPS_ESTABLISHED &&
	    (error == EHOSTUNREACH || error == ENETUNREACH ||
	    error == EHOSTDOWN)) {
		if (inp->inp_route.ro_rt) {
			rtfree(inp->inp_route.ro_rt);
			inp->inp_route.ro_rt = (struct rtentry *)NULL;
		}
	} else if (tp->t_state < TCPS_ESTABLISHED && tp->t_rxtshift > 3 &&
	    tp->t_softerror)
		tcp_drop(tp, error);
	else
		tp->t_softerror = error;
#if 0
	wakeup((caddr_t) &so->so_timeo);
	sorwakeup(so);
	sowwakeup(so);
#endif
}