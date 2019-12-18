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
struct tty {int t_state; int t_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  ECHONL ; 
 int /*<<< orphan*/  EXTPROC ; 
 int /*<<< orphan*/  FLUSHO ; 
 int ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_CNTTB ; 
 int /*<<< orphan*/  TTY_CHARMASK ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  ttyoutput (int,struct tty*) ; 

__attribute__((used)) static void
ttyecho(int c, struct tty *tp)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	if (!ISSET(tp->t_state, TS_CNTTB))
		CLR(tp->t_lflag, FLUSHO);
	if ((!ISSET(tp->t_lflag, ECHO) &&
	     (c != '\n' || !ISSET(tp->t_lflag, ECHONL))) ||
	    ISSET(tp->t_lflag, EXTPROC))
		return;
	if (ISSET(tp->t_lflag, ECHOCTL) &&
	    ((ISSET(c, TTY_CHARMASK) <= 037 && c != '\t' && c != '\n') ||
	    ISSET(c, TTY_CHARMASK) == 0177)) {
		(void)ttyoutput('^', tp);
		CLR(c, ~TTY_CHARMASK);
		if (c == 0177)
			c = '?';
		else
			c += 'A' - 1;
	}
	(void)ttyoutput(c, tp);
}