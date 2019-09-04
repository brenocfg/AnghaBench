#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int tcflag_t ;
struct TYPE_9__ {int c_cc; } ;
struct TYPE_8__ {int c_cc; } ;
struct TYPE_7__ {scalar_t__ c_cc; } ;
struct tty {int t_lflag; int t_iflag; int t_cflag; int t_state; int t_rocount; scalar_t__ t_hiwat; int t_rocol; int t_column; TYPE_5__ t_canq; TYPE_2__ t_rawq; TYPE_1__ t_outq; scalar_t__* t_cc; int /*<<< orphan*/  t_rawcc; int /*<<< orphan*/  t_cancc; } ;
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 int ALTWERASE ; 
 int BRKINT ; 
 scalar_t__ CCEQ (scalar_t__,int) ; 
 scalar_t__ CCONT (int) ; 
 int /*<<< orphan*/  CLR (int,int) ; 
 int CRTS_IFLOW ; 
 char CTRL (char) ; 
 int ECHO ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHOKE ; 
 int ECHOPRT ; 
 int EXTPROC ; 
 int FLUSHO ; 
 int /*<<< orphan*/  FLUSHQ (TYPE_2__*) ; 
 int FREAD ; 
 int FWRITE ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int IGNPAR ; 
 int IMAXBEL ; 
 int INLCR ; 
 int INPCK ; 
 int ISALPHA (int) ; 
 int ISIG ; 
 int ISSET (int,int) ; 
 int ISTRIP ; 
 int IUTF8 ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int I_HIGH_WATER ; 
 int MAX_INPUT ; 
 int NOFLSH ; 
 int NOKERNINFO ; 
 int PARMRK ; 
 int PENDIN ; 
 int /*<<< orphan*/  SET (int,int) ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int TS_ERASE ; 
 int TS_LNCH ; 
 int TS_LOCAL ; 
 int TS_TBLOCK ; 
 int TS_TTSTOP ; 
 int TS_TYPEN ; 
 scalar_t__ TTBREAKC (int,int) ; 
 int TTY_BI ; 
 int TTY_ERRORMASK ; 
 int TTY_FE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int TTY_PE ; 
 int TTY_QUOTE ; 
 size_t VDISCARD ; 
 size_t VEOF ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VLNEXT ; 
 size_t VQUIT ; 
 size_t VREPRINT ; 
 size_t VSTART ; 
 size_t VSTATUS ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 size_t VWERASE ; 
 int /*<<< orphan*/  catq (TYPE_2__*,TYPE_5__*) ; 
 int min (int,int) ; 
 scalar_t__ putc (int,TYPE_2__*) ; 
 int /*<<< orphan*/  tk_cancc ; 
 int /*<<< orphan*/  tk_nin ; 
 int /*<<< orphan*/  tk_rawcc ; 
 int ttstart (struct tty*) ; 
 int /*<<< orphan*/  ttwakeup (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_pgsignal (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyblock (struct tty*) ; 
 int /*<<< orphan*/  ttyecho (int,struct tty*) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int) ; 
 int /*<<< orphan*/  ttyinfo_locked (struct tty*) ; 
 int /*<<< orphan*/  ttyoutput (char,struct tty*) ; 
 int /*<<< orphan*/  ttypend (struct tty*) ; 
 int /*<<< orphan*/  ttyretype (struct tty*) ; 
 int /*<<< orphan*/  ttyrub (int,struct tty*) ; 
 int /*<<< orphan*/  ttystop (struct tty*,int /*<<< orphan*/ ) ; 
 int unputc (TYPE_2__*) ; 

int
ttyinput(int c, struct tty *tp)
{
	tcflag_t iflag, lflag;
	cc_t *cc;
	int i, err;
	int retval = 0;			/* default return value */

	TTY_LOCK_OWNED(tp);	/* debug assert */
        
	/*
	 * If input is pending take it first.
	 */
	lflag = tp->t_lflag;
	if (ISSET(lflag, PENDIN))
		ttypend(tp);
	/*
	 * Gather stats.
	 */
	if (ISSET(lflag, ICANON)) {
		++tk_cancc;
		++tp->t_cancc;
	} else {
		++tk_rawcc;
		++tp->t_rawcc;
	}
	++tk_nin;

	/*
	 * Block further input iff:
	 * current input > threshold AND input is available to user program
	 * AND input flow control is enabled and not yet invoked.
	 * The 3 is slop for PARMRK.
	 */
	iflag = tp->t_iflag;
	if (tp->t_rawq.c_cc + tp->t_canq.c_cc > I_HIGH_WATER - 3 &&
	    (!ISSET(lflag, ICANON) || tp->t_canq.c_cc != 0) &&
	    (ISSET(tp->t_cflag, CRTS_IFLOW) || ISSET(iflag, IXOFF)) &&
	    !ISSET(tp->t_state, TS_TBLOCK))
		ttyblock(tp);

	/* Handle exceptional conditions (break, parity, framing). */
	cc = tp->t_cc;
	err = (ISSET(c, TTY_ERRORMASK));
	if (err) {
		CLR(c, TTY_ERRORMASK);
		if (ISSET(err, TTY_BI)) {
			if (ISSET(iflag, IGNBRK)) {
				goto out;
                        }
			if (ISSET(iflag, BRKINT)) {
				ttyflush(tp, FREAD | FWRITE);
				/* SAFE: All callers drop the lock on return */
				tty_unlock(tp);
				tty_pgsignal(tp, SIGINT, 1);
				tty_lock(tp);
				goto endcase;
			}
			if (ISSET(iflag, PARMRK))
				goto parmrk;
		} else if ((ISSET(err, TTY_PE) && ISSET(iflag, INPCK))
			|| ISSET(err, TTY_FE)) {
			if (ISSET(iflag, IGNPAR)) {
				goto out;
			}
			else if (ISSET(iflag, PARMRK)) {
parmrk:
				if (tp->t_rawq.c_cc + tp->t_canq.c_cc >
				    MAX_INPUT - 3)
					goto input_overflow;
				(void)putc(0377 | TTY_QUOTE, &tp->t_rawq);
				(void)putc(0 | TTY_QUOTE, &tp->t_rawq);
				(void)putc(c | TTY_QUOTE, &tp->t_rawq);
				goto endcase;
			} else
				c = 0;
		}
	}

	if (!ISSET(tp->t_state, TS_TYPEN) && ISSET(iflag, ISTRIP))
		CLR(c, 0x80);
	if (!ISSET(lflag, EXTPROC)) {
		/*
		 * Check for literal nexting very first
		 */
		if (ISSET(tp->t_state, TS_LNCH)) {
			SET(c, TTY_QUOTE);
			CLR(tp->t_state, TS_LNCH);
		}
		/*
		 * Scan for special characters.  This code
		 * is really just a big case statement with
		 * non-constant cases.  The bottom of the
		 * case statement is labeled ``endcase'', so goto
		 * it after a case match, or similar.
		 */

		/*
		 * Control chars which aren't controlled
		 * by ICANON, ISIG, or IXON.
		 */
		if (ISSET(lflag, IEXTEN)) {
			if (CCEQ(cc[VLNEXT], c)) {
				if (ISSET(lflag, ECHO)) {
					if (ISSET(lflag, ECHOE)) {
						(void)ttyoutput('^', tp);
						(void)ttyoutput('\b', tp);
					} else
						ttyecho(c, tp);
				}
				SET(tp->t_state, TS_LNCH);
				goto endcase;
			}
			if (CCEQ(cc[VDISCARD], c)) {
				if (ISSET(lflag, FLUSHO))
					CLR(tp->t_lflag, FLUSHO);
				else {
					ttyflush(tp, FWRITE);
					ttyecho(c, tp);
					if (tp->t_rawq.c_cc + tp->t_canq.c_cc)
						ttyretype(tp);
					SET(tp->t_lflag, FLUSHO);
				}
				goto startoutput;
			}
		}
		/*
		 * Signals.
		 */
		if (ISSET(lflag, ISIG)) {
			if (CCEQ(cc[VINTR], c) || CCEQ(cc[VQUIT], c)) {
				if (!ISSET(lflag, NOFLSH))
					ttyflush(tp, FREAD | FWRITE);
				ttyecho(c, tp);
				/*
				 * SAFE: All callers drop the lock on return;
				 * SAFE: if we lose a threaded race on change
				 * SAFE: of the interrupt character, we could
				 * SAFE: have lost that race anyway due to the
				 * SAFE: scheduler executing threads in
				 * SAFE: priority order rather than "last
				 * SAFE: active thread" order (FEATURE).
				 */
				tty_unlock(tp);
				tty_pgsignal(tp,
				    CCEQ(cc[VINTR], c) ? SIGINT : SIGQUIT, 1);
				tty_lock(tp);
				goto endcase;
			}
			if (CCEQ(cc[VSUSP], c)) {
				if (!ISSET(lflag, NOFLSH))
					ttyflush(tp, FREAD);
				ttyecho(c, tp);
				/* SAFE: All callers drop the lock on return */
				tty_unlock(tp);
				tty_pgsignal(tp, SIGTSTP, 1);
				tty_lock(tp);
				goto endcase;
			}
		}
		/*
		 * Handle start/stop characters.
		 */
		if (ISSET(iflag, IXON)) {
			if (CCEQ(cc[VSTOP], c)) {
				if (!ISSET(tp->t_state, TS_TTSTOP)) {
					SET(tp->t_state, TS_TTSTOP);
                                        ttystop(tp, 0);
					goto out;
				}
				if (!CCEQ(cc[VSTART], c)) {
					goto out;
                                }
				/*
				 * if VSTART == VSTOP then toggle
				 */
				goto endcase;
			}
			if (CCEQ(cc[VSTART], c))
				goto restartoutput;
		}
		/*
		 * IGNCR, ICRNL, & INLCR
		 */
		if (c == '\r') {
			if (ISSET(iflag, IGNCR)) {
				goto out;
                        }
			else if (ISSET(iflag, ICRNL))
				c = '\n';
		} else if (c == '\n' && ISSET(iflag, INLCR))
			c = '\r';
	}
	if (!ISSET(tp->t_lflag, EXTPROC) && ISSET(lflag, ICANON)) {
		/*
		 * From here on down canonical mode character
		 * processing takes place.
		 */
		/*
		 * erase (^H / ^?)
		 */
		if (CCEQ(cc[VERASE], c)) {
			if (tp->t_rawq.c_cc) {
				if (ISSET(iflag, IUTF8)) {
					do {
						ttyrub((c = unputc(&tp->t_rawq)), tp);
					} while(tp->t_rawq.c_cc && CCONT(c));
				} else {
					ttyrub(unputc(&tp->t_rawq), tp);
				}
			}
			goto endcase;
		}
		/*
		 * kill (^U)
		 */
		if (CCEQ(cc[VKILL], c)) {
			if (ISSET(lflag, ECHOKE) &&
			    tp->t_rawq.c_cc == tp->t_rocount &&
			    !ISSET(lflag, ECHOPRT))
				while (tp->t_rawq.c_cc)
					ttyrub(unputc(&tp->t_rawq), tp);
			else {
				ttyecho(c, tp);
				if (ISSET(lflag, ECHOK) ||
				    ISSET(lflag, ECHOKE))
					ttyecho('\n', tp);
				FLUSHQ(&tp->t_rawq);
				tp->t_rocount = 0;
			}
			CLR(tp->t_state, TS_LOCAL);
			goto endcase;
		}
		/*
		 * word erase (^W)
		 */
		if (CCEQ(cc[VWERASE], c) && ISSET(lflag, IEXTEN)) {
			int ctype;

			/*
			 * erase whitespace
			 */
			while ((c = unputc(&tp->t_rawq)) == ' ' || c == '\t')
				ttyrub(c, tp);
			if (c == -1)
				goto endcase;
			/*
			 * erase last char of word and remember the
			 * next chars type (for ALTWERASE)
			 */
			ttyrub(c, tp);
			c = unputc(&tp->t_rawq);
			if (c == -1)
				goto endcase;
			if (c == ' ' || c == '\t') {
				(void)putc(c, &tp->t_rawq);
				goto endcase;
			}
			ctype = ISALPHA(c);
			/*
			 * erase rest of word
			 */
			do {
				ttyrub(c, tp);
				c = unputc(&tp->t_rawq);
				if (c == -1)
					goto endcase;
			} while (c != ' ' && c != '\t' &&
			    (!ISSET(lflag, ALTWERASE) || ISALPHA(c) == ctype));
			(void)putc(c, &tp->t_rawq);
			goto endcase;
		}
		/*
		 * reprint line (^R)
		 */
		if (CCEQ(cc[VREPRINT], c) && ISSET(lflag, IEXTEN)) {
			ttyretype(tp);
			goto endcase;
		}
		/*
		 * ^T - kernel info and generate SIGINFO
		 */
		if (CCEQ(cc[VSTATUS], c) && ISSET(lflag, IEXTEN)) {
			if (ISSET(lflag, ISIG)) {
				/* SAFE: All callers drop the lock on return */
				tty_unlock(tp);
				tty_pgsignal(tp, SIGINFO, 1);
				tty_lock(tp);
			}
			if (!ISSET(lflag, NOKERNINFO))
				ttyinfo_locked(tp);
			goto endcase;
		}
	}
	/*
	 * Check for input buffer overflow
	 */
	if (tp->t_rawq.c_cc + tp->t_canq.c_cc >= MAX_INPUT) {
input_overflow:
		if (ISSET(iflag, IMAXBEL)) {
			if (tp->t_outq.c_cc < tp->t_hiwat)
				(void)ttyoutput(CTRL('g'), tp);
		}
		goto endcase;
	}

	if (   c == 0377 && ISSET(iflag, PARMRK) && !ISSET(iflag, ISTRIP)
	     && ISSET(iflag, IGNBRK|IGNPAR) != (IGNBRK|IGNPAR))
		(void)putc(0377 | TTY_QUOTE, &tp->t_rawq);

	/*
	 * Put data char in q for user and
	 * wakeup on seeing a line delimiter.
	 */
	if (putc(c, &tp->t_rawq) >= 0) {
		if (!ISSET(lflag, ICANON)) {
			ttwakeup(tp);
			ttyecho(c, tp);
			goto endcase;
		}
		if (TTBREAKC(c, lflag)) {
			tp->t_rocount = 0;
			catq(&tp->t_rawq, &tp->t_canq);
			ttwakeup(tp);
		} else if (tp->t_rocount++ == 0)
			tp->t_rocol = tp->t_column;
		if (ISSET(tp->t_state, TS_ERASE)) {
			/*
			 * end of prterase \.../
			 */
			CLR(tp->t_state, TS_ERASE);
			(void)ttyoutput('/', tp);
		}
		i = tp->t_column;
		ttyecho(c, tp);
		if (CCEQ(cc[VEOF], c) && ISSET(lflag, ECHO)) {
			/*
			 * Place the cursor over the '^' of the ^D.
			 */
			i = min(2, tp->t_column - i);
			while (i > 0) {
				(void)ttyoutput('\b', tp);
				i--;
			}
		}
	}

endcase:
	/*
	 * IXANY means allow any character to restart output.
	 */
	if (ISSET(tp->t_state, TS_TTSTOP) &&
	    !ISSET(iflag, IXANY) && cc[VSTART] != cc[VSTOP]) {
	    	goto out;
        }

restartoutput:
	CLR(tp->t_lflag, FLUSHO);
	CLR(tp->t_state, TS_TTSTOP);

startoutput:
	/* Start the output */
	retval = ttstart(tp);

out:
	return (retval);
}