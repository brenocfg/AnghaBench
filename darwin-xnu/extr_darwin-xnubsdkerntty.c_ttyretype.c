#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  c_cc; } ;
struct tty {scalar_t__* t_cc; scalar_t__ t_rocol; TYPE_1__ t_rawq; int /*<<< orphan*/  t_rocount; int /*<<< orphan*/  t_state; TYPE_1__ t_canq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ERASE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 size_t VREPRINT ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/ * firstc (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * nextc (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ttyecho (int,struct tty*) ; 
 int /*<<< orphan*/  ttyoutput (char,struct tty*) ; 

__attribute__((used)) static void
ttyretype(struct tty *tp)
{
	u_char *cp;
	int c;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	/* Echo the reprint character. */
	if (tp->t_cc[VREPRINT] != _POSIX_VDISABLE)
		ttyecho(tp->t_cc[VREPRINT], tp);

	(void)ttyoutput('\n', tp);

	/*
	 * FREEBSD XXX
	 * FIX: NEXTC IS BROKEN - DOESN'T CHECK QUOTE
	 * BIT OF FIRST CHAR.
	 */
	for (cp = firstc(&tp->t_canq, &c); cp; cp = nextc(&tp->t_canq, cp, &c))
		ttyecho(c, tp);
	for (cp = firstc(&tp->t_rawq, &c); cp; cp = nextc(&tp->t_rawq, cp, &c))
		ttyecho(c, tp);
	CLR(tp->t_state, TS_ERASE);

	tp->t_rocount = tp->t_rawq.c_cc;
	tp->t_rocol = 0;
}