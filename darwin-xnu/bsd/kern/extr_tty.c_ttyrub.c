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
struct TYPE_3__ {scalar_t__ c_cc; } ;
struct tty {int t_lflag; scalar_t__ t_rocount; int t_iflag; int t_column; int t_state; int t_rocol; int* t_cc; TYPE_1__ t_rawq; } ;

/* Variables and functions */
#define  BACKSPACE 134 
 int CCLASS (int) ; 
 int /*<<< orphan*/  CCONT (int) ; 
 int /*<<< orphan*/  CLR (int,int /*<<< orphan*/ ) ; 
#define  CONTROL 133 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  ECHOE ; 
 int /*<<< orphan*/  ECHOPRT ; 
 int /*<<< orphan*/  EXTPROC ; 
 int /*<<< orphan*/  FLUSHO ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUTF8 ; 
#define  NEWLINE 132 
#define  ORDINARY 131 
 char* PANICSTR ; 
#define  RETURN 130 
 int /*<<< orphan*/  SET (int,int /*<<< orphan*/ ) ; 
#define  TAB 129 
 int /*<<< orphan*/  TS_CNTTB ; 
 int /*<<< orphan*/  TS_ERASE ; 
 int /*<<< orphan*/  TTY_CHARMASK ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 char TTY_QUOTE ; 
 size_t VERASE ; 
#define  VTAB 128 
 int /*<<< orphan*/ * firstc (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * nextc (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  ttyecho (int,struct tty*) ; 
 int /*<<< orphan*/  ttyoutput (char,struct tty*) ; 
 int /*<<< orphan*/  ttyretype (struct tty*) ; 
 int /*<<< orphan*/  ttyrubo (struct tty*,int) ; 

__attribute__((used)) static void
ttyrub(int c, struct tty *tp)
{
	u_char *cp;
	int savecol;
	int tabc;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	if (!ISSET(tp->t_lflag, ECHO) || ISSET(tp->t_lflag, EXTPROC))
		return;
	CLR(tp->t_lflag, FLUSHO);
	if (ISSET(tp->t_lflag, ECHOE)) {
		if (tp->t_rocount == 0) {
			/*
			 * Messed up by ttwrite; retype
			 */
			ttyretype(tp);
			return;
		}
		if (c == ('\t' | TTY_QUOTE) || c == ('\n' | TTY_QUOTE))
			ttyrubo(tp, 2);
		else {
			CLR(c, ~TTY_CHARMASK);
			switch (CCLASS(c)) {
			case ORDINARY:
				if(!(ISSET(tp->t_iflag, IUTF8) && CCONT(c))) {
					ttyrubo(tp, 1);
				}
				break;
			case BACKSPACE:
			case CONTROL:
			case NEWLINE:
			case RETURN:
			case VTAB:
				if (ISSET(tp->t_lflag, ECHOCTL))
					ttyrubo(tp, 2);
				break;
			case TAB:
				if (tp->t_rocount < tp->t_rawq.c_cc) {
					ttyretype(tp);
					return;
				}
				savecol = tp->t_column;
				SET(tp->t_state, TS_CNTTB);
				SET(tp->t_lflag, FLUSHO);
				tp->t_column = tp->t_rocol;
				for (cp = firstc(&tp->t_rawq, &tabc); cp;
				    cp = nextc(&tp->t_rawq, cp, &tabc))
					ttyecho(tabc, tp);
				CLR(tp->t_lflag, FLUSHO);
				CLR(tp->t_state, TS_CNTTB);

				/* savecol will now be length of the tab. */
				savecol -= tp->t_column;
				tp->t_column += savecol;
				if (savecol > 8)
					savecol = 8;	/* overflow fixup */
				while (--savecol >= 0)
					(void)ttyoutput('\b', tp);
				break;
			default:			/* XXX */
#define	PANICSTR	"ttyrub: would panic c = %d, val = %d\n"
				printf(PANICSTR, c, CCLASS(c));
#ifdef notdef
				panic(PANICSTR, c, CCLASS(c));
#endif
			}
		}
	} else if (ISSET(tp->t_lflag, ECHOPRT)) {
		if (!ISSET(tp->t_state, TS_ERASE)) {
			SET(tp->t_state, TS_ERASE);
			(void)ttyoutput('\\', tp);
		}
		ttyecho(c, tp);
	} else
		ttyecho(tp->t_cc[VERASE], tp);
	--tp->t_rocount;
}