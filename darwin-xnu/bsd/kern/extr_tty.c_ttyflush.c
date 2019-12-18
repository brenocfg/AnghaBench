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
struct tty {int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_state; int /*<<< orphan*/  t_iflag; scalar_t__ t_rocol; scalar_t__ t_rocount; int /*<<< orphan*/  t_lflag; int /*<<< orphan*/  t_rawq; int /*<<< orphan*/  t_canq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLUSHQ (int /*<<< orphan*/ *) ; 
 int FREAD ; 
 int FWRITE ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXOFF ; 
 int /*<<< orphan*/  PENDIN ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSA_OCOMPLETE (struct tty*) ; 
 int /*<<< orphan*/  TS_LOCAL ; 
 int /*<<< orphan*/  TS_SO_OCOMPLETE ; 
 int /*<<< orphan*/  TS_TBLOCK ; 
 int /*<<< orphan*/  TS_TTSTOP ; 
 int /*<<< orphan*/  TTOPRI ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int hz ; 
 int /*<<< orphan*/  ttwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttwwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttysleep (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ttystop (struct tty*,int) ; 
 int /*<<< orphan*/  ttyunblock (struct tty*) ; 

void
ttyflush(struct tty *tp, int rw)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

#if 0
again:
#endif
	if (rw & FWRITE) {
		FLUSHQ(&tp->t_outq);
		CLR(tp->t_state, TS_TTSTOP);
	}
        ttystop(tp, rw);
        if (rw & FREAD) {
		FLUSHQ(&tp->t_canq);
		FLUSHQ(&tp->t_rawq);
		CLR(tp->t_lflag, PENDIN);
		tp->t_rocount = 0;
		tp->t_rocol = 0;
		CLR(tp->t_state, TS_LOCAL);
		ttwakeup(tp);
		if (ISSET(tp->t_state, TS_TBLOCK)) {
			if (rw & FWRITE)
				FLUSHQ(&tp->t_outq);
			ttyunblock(tp);

			/*
			 * Don't let leave any state that might clobber the
			 * next line discipline (although we should do more
			 * to send the START char).  Not clearing the state
			 * may have caused the "putc to a clist with no
			 * reserved cblocks" panic/printf.
			 */
			CLR(tp->t_state, TS_TBLOCK);

#if 0 /* forget it, sleeping isn't always safe and we don't know when it is */
			if (ISSET(tp->t_iflag, IXOFF)) {
				/*
				 * XXX wait a bit in the hope that the stop
				 * character (if any) will go out.  Waiting
				 * isn't good since it allows races.  This
				 * will be fixed when the stop character is
				 * put in a special queue.  Don't bother with
				 * the checks in ttywait() since the timeout
				 * will save us.
				 */
				SET(tp->t_state, TS_SO_OCOMPLETE);
				ttysleep(tp, TSA_OCOMPLETE(tp), TTOPRI,
					 "ttyfls", hz / 10);
				/*
				 * Don't try sending the stop character again.
				 */
				CLR(tp->t_state, TS_TBLOCK);
				goto again;
			}
#endif
		}
	}
	if (rw & FWRITE) {
		FLUSHQ(&tp->t_outq);
		ttwwakeup(tp);
	}
}