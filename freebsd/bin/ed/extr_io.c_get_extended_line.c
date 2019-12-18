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
 int /*<<< orphan*/  REALLOC (char*,int,int,int /*<<< orphan*/ *) ; 
 char* errmsg ; 
 int get_tty_line () ; 
 int /*<<< orphan*/  has_trailing_escape (char*,char*) ; 
 char* ibuf ; 
 char* ibufp ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

char *
get_extended_line(int *sizep, int nonl)
{
	static char *cvbuf = NULL;		/* buffer */
	static int cvbufsz = 0;			/* buffer size */

	int l, n;
	char *t = ibufp;

	while (*t++ != '\n')
		;
	if ((l = t - ibufp) < 2 || !has_trailing_escape(ibufp, ibufp + l - 1)) {
		*sizep = l;
		return ibufp;
	}
	*sizep = -1;
	REALLOC(cvbuf, cvbufsz, l, NULL);
	memcpy(cvbuf, ibufp, l);
	*(cvbuf + --l - 1) = '\n'; 	/* strip trailing esc */
	if (nonl) l--; 			/* strip newline */
	for (;;) {
		if ((n = get_tty_line()) < 0)
			return NULL;
		else if (n == 0 || ibuf[n - 1] != '\n') {
			errmsg = "unexpected end-of-file";
			return NULL;
		}
		REALLOC(cvbuf, cvbufsz, l + n, NULL);
		memcpy(cvbuf + l, ibuf, n);
		l += n;
		if (n < 2 || !has_trailing_escape(cvbuf, cvbuf + l - 1))
			break;
		*(cvbuf + --l - 1) = '\n'; 	/* strip trailing esc */
		if (nonl) l--; 			/* strip newline */
	}
	REALLOC(cvbuf, cvbufsz, l + 1, NULL);
	cvbuf[l] = '\0';
	*sizep = l;
	return cvbuf;
}