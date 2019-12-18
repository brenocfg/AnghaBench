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
 int /*<<< orphan*/  REALLOC (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 char* errmsg ; 
 int get_tty_line () ; 
 char* ibuf ; 
 char* ibufp ; 
 int /*<<< orphan*/  isglobal ; 
 char* rhbuf ; 
 size_t rhbufi ; 
 int /*<<< orphan*/  rhbufsz ; 
 int /*<<< orphan*/  stdin ; 

char *
extract_subst_template(void)
{
	int n = 0;
	int i = 0;
	char c;
	char delimiter = *ibufp++;

	if (*ibufp == '%' && *(ibufp + 1) == delimiter) {
		ibufp++;
		if (!rhbuf)
			errmsg = "no previous substitution";
		return rhbuf;
	}
	while (*ibufp != delimiter) {
		REALLOC(rhbuf, rhbufsz, i + 2, NULL);
		if ((c = rhbuf[i++] = *ibufp++) == '\n' && *ibufp == '\0') {
			i--, ibufp--;
			break;
		} else if (c != '\\')
			;
		else if ((rhbuf[i++] = *ibufp++) != '\n')
			;
		else if (!isglobal) {
			while ((n = get_tty_line()) == 0 ||
			    (n > 0 && ibuf[n - 1] != '\n'))
				clearerr(stdin);
			if (n < 0)
				return NULL;
		}
	}
	REALLOC(rhbuf, rhbufsz, i + 1, NULL);
	rhbuf[rhbufi = i] = '\0';
	return  rhbuf;
}