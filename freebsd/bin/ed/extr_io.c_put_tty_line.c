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
 int ERR ; 
 char* ESCAPES ; 
 char* ESCCHARS ; 
 int GLS ; 
 int GNP ; 
 int cols ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_tty_line () ; 
 int /*<<< orphan*/  isglobal ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int rows ; 
 int /*<<< orphan*/  scripted ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char const) ; 

int
put_tty_line(const char *s, int l, long n, int gflag)
{
	int col = 0;
	int lc = 0;
	char *cp;

	if (gflag & GNP) {
		printf("%ld\t", n);
		col = 8;
	}
	for (; l--; s++) {
		if ((gflag & GLS) && ++col > cols) {
			fputs("\\\n", stdout);
			col = 1;
#ifndef BACKWARDS
			if (!scripted && !isglobal && ++lc > rows) {
				lc = 0;
				fputs("Press <RETURN> to continue... ", stdout);
				fflush(stdout);
				if (get_tty_line() < 0)
					return ERR;
			}
#endif
		}
		if (gflag & GLS) {
			if (31 < *s && *s < 127 && *s != '\\')
				putchar(*s);
			else {
				putchar('\\');
				col++;
				if (*s && (cp = strchr(ESCAPES, *s)) != NULL)
					putchar(ESCCHARS[cp - ESCAPES]);
				else {
					putchar((((unsigned char) *s & 0300) >> 6) + '0');
					putchar((((unsigned char) *s & 070) >> 3) + '0');
					putchar(((unsigned char) *s & 07) + '0');
					col += 2;
				}
			}

		} else
			putchar(*s);
	}
#ifndef BACKWARDS
	if (gflag & GLS)
		putchar('$');
#endif
	putchar('\n');
	return 0;
}