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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  tcflag_t ;
struct tty {int t_column; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_lflag; scalar_t__ t_outcc; int /*<<< orphan*/  t_oflag; } ;

/* Variables and functions */
#define  BACKSPACE 133 
 int CCLASS (int) ; 
 int CEOT ; 
 int /*<<< orphan*/  CLR (int,int /*<<< orphan*/ ) ; 
#define  CONTROL 132 
 int /*<<< orphan*/  EXTPROC ; 
 int /*<<< orphan*/  FLUSHO ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NEWLINE 131 
 int /*<<< orphan*/  OCRNL ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  ONOCR ; 
 int /*<<< orphan*/  ONOEOT ; 
 int /*<<< orphan*/  OPOST ; 
#define  ORDINARY 130 
 int /*<<< orphan*/  OXTABS ; 
#define  RETURN 129 
#define  TAB 128 
 int /*<<< orphan*/  TTY_CHARMASK ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 scalar_t__ b_to_q (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ tk_nout ; 

__attribute__((used)) static int
ttyoutput(int c, struct tty *tp)
{
	tcflag_t oflag;
	int col;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	oflag = tp->t_oflag;
	if (!ISSET(oflag, OPOST)) {
		if (ISSET(tp->t_lflag, FLUSHO))
			return (-1);
		if (putc(c, &tp->t_outq))
			return (c);
		tk_nout++;
		tp->t_outcc++;
		return (-1);
	}
	/*
	 * Do tab expansion if OXTABS is set.  Special case if we external
	 * processing, we don't do the tab expansion because we'll probably
	 * get it wrong.  If tab expansion needs to be done, let it happen
	 * externally.
	 */
	CLR(c, ~TTY_CHARMASK);
	if (c == '\t' &&
	    ISSET(oflag, OXTABS) && !ISSET(tp->t_lflag, EXTPROC)) {
		col = c = 8 - (tp->t_column & 7);
		if (!ISSET(tp->t_lflag, FLUSHO)) {
			c -= b_to_q((const u_char *)"        ", c, &tp->t_outq);
			tk_nout += c;
			tp->t_outcc += c;
		}
		tp->t_column += c;
		return (c == col ? -1 : '\t');
	}
	if (c == CEOT && ISSET(oflag, ONOEOT))
		return (-1);

	/*
	 * Newline translation: if ONLCR is set,
	 * translate newline into "\r\n".
	 */
	if (c == '\n' && ISSET(tp->t_oflag, ONLCR)) {
		tk_nout++;
		tp->t_outcc++;
		if (putc('\r', &tp->t_outq))
			return (c);
	}
        /* If OCRNL is set, translate "\r" into "\n". */
        else if (c == '\r' && ISSET(tp->t_oflag, OCRNL))
                c = '\n';
        /* If ONOCR is set, don't transmit CRs when on column 0. */
        else if (c == '\r' && ISSET(tp->t_oflag, ONOCR) && tp->t_column == 0)
                return (-1);
	tk_nout++;
	tp->t_outcc++;
	if (!ISSET(tp->t_lflag, FLUSHO) && putc(c, &tp->t_outq))
		return (c);

	col = tp->t_column;
	switch (CCLASS(c)) {
	case BACKSPACE:
		if (col > 0)
			--col;
		break;
	case CONTROL:
		break;
	case NEWLINE:
	case RETURN:
		col = 0;
		break;
	case ORDINARY:
		++col;
		break;
	case TAB:
		col = (col + 8) & ~7;
		break;
	}
	tp->t_column = col;
	return (-1);
}