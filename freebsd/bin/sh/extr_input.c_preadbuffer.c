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
struct TYPE_4__ {char* buf; scalar_t__ fd; TYPE_1__* strpush; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ap; } ;
typedef  int /*<<< orphan*/  HistEvent ;

/* Variables and functions */
 int EOF_NLEFT ; 
 int /*<<< orphan*/  H_ADD ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int PEOF ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ ) ; 
 scalar_t__ hist ; 
 int /*<<< orphan*/  history (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  out2str (char*) ; 
 TYPE_2__* parsefile ; 
 int parselleft ; 
 char* parsenextc ; 
 int parsenleft ; 
 int /*<<< orphan*/  popstring () ; 
 int preadfd () ; 
 char* strchrnul (char*,char) ; 
 size_t strspn (char*,char*) ; 
 scalar_t__ vflag ; 
 int whichprompt ; 

int
preadbuffer(void)
{
	char *p, *q, *r, *end;
	char savec;

	while (parsefile->strpush) {
		/*
		 * Add a space to the end of an alias to ensure that the
		 * alias remains in use while parsing its last word.
		 * This avoids alias recursions.
		 */
		if (parsenleft == -1 && parsefile->strpush->ap != NULL)
			return ' ';
		popstring();
		if (--parsenleft >= 0)
			return (*parsenextc++);
	}
	if (parsenleft == EOF_NLEFT || parsefile->buf == NULL)
		return PEOF;

again:
	if (parselleft <= 0) {
		if ((parselleft = preadfd()) == -1) {
			parselleft = parsenleft = EOF_NLEFT;
			return PEOF;
		}
	}

	p = parsefile->buf + (parsenextc - parsefile->buf);
	end = p + parselleft;
	*end = '\0';
	q = strchrnul(p, '\n');
	if (q != end && *q == '\0') {
		/* delete nul characters */
		for (r = q; q != end; q++) {
			if (*q != '\0')
				*r++ = *q;
		}
		parselleft -= end - r;
		if (parselleft == 0)
			goto again;
		end = p + parselleft;
		*end = '\0';
		q = strchrnul(p, '\n');
	}
	if (q == end) {
		parsenleft = parselleft;
		parselleft = 0;
	} else /* *q == '\n' */ {
		q++;
		parsenleft = q - parsenextc;
		parselleft -= parsenleft;
	}
	parsenleft--;

	savec = *q;
	*q = '\0';

#ifndef NO_HISTORY
	if (parsefile->fd == 0 && hist &&
	    parsenextc[strspn(parsenextc, " \t\n")] != '\0') {
		HistEvent he;
		INTOFF;
		history(hist, &he, whichprompt == 1 ? H_ENTER : H_ADD,
		    parsenextc);
		INTON;
	}
#endif

	if (vflag) {
		out2str(parsenextc);
		flushout(out2);
	}

	*q = savec;

	return *parsenextc++;
}