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
 scalar_t__ equal (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 

int
main(int argc, char *argv[])
{
	char **ap;
	char *p;
	char c;
	int count;
	int nflag = 0;
#ifndef eflag
	int eflag = 0;
#endif

	ap = argv;
	if (argc)
		ap++;
	if ((p = *ap) != NULL) {
		if (equal(p, "-n")) {
			nflag++;
			ap++;
		} else if (equal(p, "-e")) {
#ifndef eflag
			eflag++;
#endif
			ap++;
		}
	}
	while ((p = *ap++) != NULL) {
		while ((c = *p++) != '\0') {
			if (c == '\\' && eflag) {
				switch (*p++) {
				case 'a':  c = '\a';  break;
				case 'b':  c = '\b';  break;
				case 'c':  return 0;		/* exit */
				case 'e':  c = '\033';  break;
				case 'f':  c = '\f';  break;
				case 'n':  c = '\n';  break;
				case 'r':  c = '\r';  break;
				case 't':  c = '\t';  break;
				case 'v':  c = '\v';  break;
				case '\\':  break;		/* c = '\\' */
				case '0':
					c = 0;
					count = 3;
					while (--count >= 0 && (unsigned)(*p - '0') < 8)
						c = (c << 3) + (*p++ - '0');
					break;
				default:
					p--;
					break;
				}
			}
			putchar(c);
		}
		if (*ap)
			putchar(' ');
	}
	if (! nflag)
		putchar('\n');
	return 0;
}