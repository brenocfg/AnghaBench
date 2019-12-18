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
typedef  int wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  Popwchar (char const*,int) ; 
 int mbtowc (int*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multibyte ; 
 int /*<<< orphan*/  valid_range (int,int) ; 

int
gmatch(const char *s, const char *p)
{
	const char	*olds;
	wchar_t		scc, c;
	int 		n;
	wchar_t		cl;

	olds = s;
	n = mbtowc(&cl, s, MB_LEN_MAX);
	if (n <= 0) {
		s++;
		scc = n;
	} else {
		scc = cl;
		s += n;
	}
	n = mbtowc(&cl, p, MB_LEN_MAX);
	if (n < 0)
		return (0);
	if (n == 0)
		return (scc == 0);
	p += n;
	c = cl;

	switch (c) {
	case '[':
		if (scc <= 0)
			return (0);
	{
			int ok;
			wchar_t lc = 0;
			int notflag = 0;

			ok = 0;
			if (*p == '!') {
				notflag = 1;
				p++;
			}
			Popwchar(p, c);
			do
			{
				if (c == '-' && lc && *p != ']') {
					Popwchar(p, c);
					if (c == '\\') {
						Popwchar(p, c);
					}
					if (notflag) {
						if (!multibyte ||
						    valid_range(lc, c)) {
							if (scc < lc || scc > c)
								ok++;
							else
								return (0);
						}
					} else {
						if (!multibyte ||
						    valid_range(lc, c))
							if (lc <= scc &&
							    scc <= c)
								ok++;
					}
				} else if (c == '\\') {
					/* skip to quoted character */
					Popwchar(p, c);
				}
				lc = c;
				if (notflag) {
					if (scc != lc)
						ok++;
					else
						return (0);
				}
				else
				{
					if (scc == lc)
						ok++;
				}
				Popwchar(p, c);
			} while (c != ']');
			return (ok ? gmatch(s, p) : 0);
		}

	case '\\':
		/* skip to quoted character and see if it matches */
		Popwchar(p, c);

	default:
		if (c != scc)
			return (0);
			/*FALLTHRU*/

	case '?':
		return (scc > 0 ? gmatch(s, p) : 0);

	case '*':
		while (*p == '*')
			p++;

		if (*p == 0)
			return (1);
		s = olds;
		while (*s) {
			if (gmatch(s, p))
				return (1);
			n = mbtowc(&cl, s, MB_LEN_MAX);
			if (n < 0)
				/* skip past illegal byte sequence */
				s++;
			else
				s += n;
		}
		return (0);
	}
}