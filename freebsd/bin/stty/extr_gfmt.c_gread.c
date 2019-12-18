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
typedef  long u_long ;
struct termios {long c_cflag; long c_iflag; long c_ispeed; long c_lflag; long c_oflag; long c_ospeed; long* c_cc; } ;
struct cchar {char* name; size_t sub; } ;

/* Variables and functions */
 scalar_t__ CHK (char*) ; 
 size_t VMIN ; 
 size_t VTIME ; 
 struct cchar* cchars1 ; 
 int /*<<< orphan*/  gerr (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,long*) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 

void
gread(struct termios *tp, char *s)
{
	struct cchar *cp;
	char *ep, *p;
	long tmp;

	if ((s = strchr(s, ':')) == NULL)
		gerr(NULL);
	for (++s; s != NULL;) {
		p = strsep(&s, ":\0");
		if (!p || !*p)
			break;
		if (!(ep = strchr(p, '=')))
			gerr(p);
		*ep++ = '\0';
		(void)sscanf(ep, "%lx", (u_long *)&tmp);

#define	CHK(s)	(*p == s[0] && !strcmp(p, s))
		if (CHK("cflag")) {
			tp->c_cflag = tmp;
			continue;
		}
		if (CHK("iflag")) {
			tp->c_iflag = tmp;
			continue;
		}
		if (CHK("ispeed")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_ispeed = tmp;
			continue;
		}
		if (CHK("lflag")) {
			tp->c_lflag = tmp;
			continue;
		}
		if (CHK("oflag")) {
			tp->c_oflag = tmp;
			continue;
		}
		if (CHK("ospeed")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_ospeed = tmp;
			continue;
		}
		for (cp = cchars1; cp->name != NULL; ++cp)
			if (CHK(cp->name)) {
				if (cp->sub == VMIN || cp->sub == VTIME)
					(void)sscanf(ep, "%ld", &tmp);
				tp->c_cc[cp->sub] = tmp;
				break;
			}
		if (cp->name == NULL)
			gerr(p);
	}
}