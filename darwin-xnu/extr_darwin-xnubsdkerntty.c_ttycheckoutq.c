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
struct uthread {int /*<<< orphan*/  uu_siglist; } ;
struct TYPE_2__ {int c_cc; } ;
struct tty {int t_hiwat; int /*<<< orphan*/  t_state; TYPE_1__ t_outq; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int OBUFSIZ ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSA_OLOWAT (struct tty*) ; 
 int /*<<< orphan*/  TS_SO_OLOWAT ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ttstart (struct tty*) ; 
 int /*<<< orphan*/  ttysleep (struct tty*,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

int
ttycheckoutq(struct tty *tp, int wait)
{
	int hiwat;
	sigset_t oldsig;
	struct uthread *ut;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	ut = (struct uthread *)get_bsdthread_info(current_thread());

	hiwat = tp->t_hiwat;
	oldsig = wait ? ut->uu_siglist : 0;
	if (tp->t_outq.c_cc > hiwat + OBUFSIZ + 100)
		while (tp->t_outq.c_cc > hiwat) {
			ttstart(tp);
			if (tp->t_outq.c_cc <= hiwat)
				break;
			if (wait == 0 || ut->uu_siglist != oldsig) {
				return (0);
			}
			SET(tp->t_state, TS_SO_OLOWAT);
			ttysleep(tp, TSA_OLOWAT(tp), PZERO - 1, "ttoutq", hz);
		}
	return (1);
}