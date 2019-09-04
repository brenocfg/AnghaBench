#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ c_cc; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct tty {scalar_t__ t_lowat; int /*<<< orphan*/  t_state; TYPE_1__ t_outq; TYPE_2__ t_wsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TSA_OCOMPLETE (struct tty*) ; 
 int /*<<< orphan*/  TSA_OLOWAT (struct tty*) ; 
 int TS_BUSY ; 
 int TS_SO_OCOMPLETE ; 
 int TS_SO_OLOWAT ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  selwakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
ttwwakeup(struct tty *tp)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	if (tp->t_outq.c_cc <= tp->t_lowat) {
		selwakeup(&tp->t_wsel);
		KNOTE(&tp->t_wsel.si_note, 1);
	}
	if (ISSET(tp->t_state, TS_BUSY | TS_SO_OCOMPLETE) ==
	    TS_SO_OCOMPLETE && tp->t_outq.c_cc == 0) {
		CLR(tp->t_state, TS_SO_OCOMPLETE);
		wakeup(TSA_OCOMPLETE(tp));
	}
	if (ISSET(tp->t_state, TS_SO_OLOWAT) &&
	    tp->t_outq.c_cc <= tp->t_lowat) {
		CLR(tp->t_state, TS_SO_OLOWAT);
		wakeup(TSA_OLOWAT(tp));
	}
}