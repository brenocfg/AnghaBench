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
#define  EOF 128 
 int ERR ; 
 int /*<<< orphan*/  REALLOC (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 char* errmsg ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getchar () ; 
 char* ibuf ; 
 char* ibufp ; 
 int /*<<< orphan*/  ibufsz ; 
 int isbinary ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
get_tty_line(void)
{
	int oi = 0;
	int i = 0;
	int c;

	for (;;)
		switch (c = getchar()) {
		default:
			oi = 0;
			REALLOC(ibuf, ibufsz, i + 2, ERR);
			if (!(ibuf[i++] = c)) isbinary = 1;
			if (c != '\n')
				continue;
			lineno++;
			ibuf[i] = '\0';
			ibufp = ibuf;
			return i;
		case EOF:
			if (ferror(stdin)) {
				fprintf(stderr, "stdin: %s\n", strerror(errno));
				errmsg = "cannot read stdin";
				clearerr(stdin);
				ibufp = NULL;
				return ERR;
			} else {
				clearerr(stdin);
				if (i != oi) {
					oi = i;
					continue;
				} else if (i)
					ibuf[i] = '\0';
				ibufp = ibuf;
				return i;
			}
		}
}