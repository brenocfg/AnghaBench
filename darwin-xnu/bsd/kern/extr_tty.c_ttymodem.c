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
struct tty {int /*<<< orphan*/  t_state; TYPE_1__* t_session; int /*<<< orphan*/  t_cflag; } ;
struct TYPE_2__ {scalar_t__ s_leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FREAD ; 
 int FWRITE ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDMBUF ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  TSA_CARR_ON (struct tty*) ; 
 int /*<<< orphan*/  TS_CARR_ON ; 
 int /*<<< orphan*/  TS_CAR_OFLOW ; 
 int /*<<< orphan*/  TS_CONNECTED ; 
 int /*<<< orphan*/  TS_ISOPEN ; 
 int /*<<< orphan*/  TS_TTSTOP ; 
 int /*<<< orphan*/  TS_ZOMBIE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  psignal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttstart (struct tty*) ; 
 int /*<<< orphan*/  ttwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttwwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int) ; 
 int /*<<< orphan*/  ttystop (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
ttymodem(struct tty *tp, int flag)
{
	int rval = 1;		/* default return value */

	TTY_LOCK_OWNED(tp);	/* debug assert */

	if (ISSET(tp->t_state, TS_CARR_ON) && ISSET(tp->t_cflag, MDMBUF)) {
		/*
		 * MDMBUF: do flow control according to carrier flag
		 * XXX TS_CAR_OFLOW doesn't do anything yet.  TS_TTSTOP
		 * works if IXON and IXANY are clear.
		 */
		if (flag) {
			CLR(tp->t_state, TS_CAR_OFLOW);
			CLR(tp->t_state, TS_TTSTOP);
			ttstart(tp);
		} else if (!ISSET(tp->t_state, TS_CAR_OFLOW)) {
			SET(tp->t_state, TS_CAR_OFLOW);
			SET(tp->t_state, TS_TTSTOP);
                        ttystop(tp, 0);
		}
	} else if (flag == 0) {
		/*
		 * Lost carrier.
		 */
		CLR(tp->t_state, TS_CARR_ON);
		if (ISSET(tp->t_state, TS_ISOPEN) &&
		    !ISSET(tp->t_cflag, CLOCAL)) {
			SET(tp->t_state, TS_ZOMBIE);
			CLR(tp->t_state, TS_CONNECTED);
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			ttyflush(tp, FREAD | FWRITE);
			rval = 0;
			goto out;
		}
	} else {
		/*
		 * Carrier now on.
		 */
		SET(tp->t_state, TS_CARR_ON);
		if (!ISSET(tp->t_state, TS_ZOMBIE))
			SET(tp->t_state, TS_CONNECTED);
		wakeup(TSA_CARR_ON(tp));
		ttwakeup(tp);
		ttwwakeup(tp);
	}

out:
	return (rval);
}