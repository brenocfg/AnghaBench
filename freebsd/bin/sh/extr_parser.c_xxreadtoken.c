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

/* Variables and functions */
 int /*<<< orphan*/  BASESYNTAX ; 
#define  PEOF 128 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAND ; 
 int /*<<< orphan*/  TBACKGND ; 
 int /*<<< orphan*/  TENDCASE ; 
 int /*<<< orphan*/  TEOF ; 
 int /*<<< orphan*/  TFALLTHRU ; 
 int /*<<< orphan*/  TLP ; 
 int /*<<< orphan*/  TNL ; 
 int /*<<< orphan*/  TOR ; 
 int /*<<< orphan*/  TPIPE ; 
 int /*<<< orphan*/  TRP ; 
 int /*<<< orphan*/  TSEMI ; 
 scalar_t__ doprompt ; 
 int lasttoken ; 
 scalar_t__ needprompt ; 
 char pgetc () ; 
 char pgetc_linecont () ; 
 int pgetc_macro () ; 
 int /*<<< orphan*/  plinno ; 
 int /*<<< orphan*/  pungetc () ; 
 int readtoken1 (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprompt (int) ; 
 int /*<<< orphan*/  startlinno ; 
 scalar_t__ tokpushback ; 

__attribute__((used)) static int
xxreadtoken(void)
{
	int c;

	if (tokpushback) {
		tokpushback = 0;
		return lasttoken;
	}
	if (needprompt) {
		setprompt(2);
		needprompt = 0;
	}
	startlinno = plinno;
	for (;;) {	/* until token or start of word found */
		c = pgetc_macro();
		switch (c) {
		case ' ': case '\t':
			continue;
		case '#':
			while ((c = pgetc()) != '\n' && c != PEOF);
			pungetc();
			continue;
		case '\\':
			if (pgetc() == '\n') {
				startlinno = ++plinno;
				if (doprompt)
					setprompt(2);
				else
					setprompt(0);
				continue;
			}
			pungetc();
			/* FALLTHROUGH */
		default:
			return readtoken1(c, BASESYNTAX, (char *)NULL, 0);
		case '\n':
			plinno++;
			needprompt = doprompt;
			RETURN(TNL);
		case PEOF:
			RETURN(TEOF);
		case '&':
			if (pgetc_linecont() == '&')
				RETURN(TAND);
			pungetc();
			RETURN(TBACKGND);
		case '|':
			if (pgetc_linecont() == '|')
				RETURN(TOR);
			pungetc();
			RETURN(TPIPE);
		case ';':
			c = pgetc_linecont();
			if (c == ';')
				RETURN(TENDCASE);
			else if (c == '&')
				RETURN(TFALLTHRU);
			pungetc();
			RETURN(TSEMI);
		case '(':
			RETURN(TLP);
		case ')':
			RETURN(TRP);
		}
	}
#undef RETURN
}