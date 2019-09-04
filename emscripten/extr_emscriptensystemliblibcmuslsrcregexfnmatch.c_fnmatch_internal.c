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
 int BRACKET ; 
 int END ; 
 int FNM_CASEFOLD ; 
 int FNM_NOMATCH ; 
 int FNM_PERIOD ; 
 int MB_CUR_MAX ; 
 int QUESTION ; 
#define  STAR 129 
#define  UNMATCHABLE 128 
 int casefold (int) ; 
 int /*<<< orphan*/  match_bracket (char const*,int,int) ; 
 int pat_next (char const*,int,size_t*,int) ; 
 int str_next (char const*,int,size_t*) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static int fnmatch_internal(const char *pat, size_t m, const char *str, size_t n, int flags)
{
	const char *p, *ptail, *endpat;
	const char *s, *stail, *endstr;
	size_t pinc, sinc, tailcnt=0;
	int c, k, kfold;

	if (flags & FNM_PERIOD) {
		if (*str == '.' && *pat != '.')
			return FNM_NOMATCH;
	}
	for (;;) {
		switch ((c = pat_next(pat, m, &pinc, flags))) {
		case UNMATCHABLE:
			return FNM_NOMATCH;
		case STAR:
			pat++;
			m--;
			break;
		default:
			k = str_next(str, n, &sinc);
			if (k <= 0)
				return (c==END) ? 0 : FNM_NOMATCH;
			str += sinc;
			n -= sinc;
			kfold = flags & FNM_CASEFOLD ? casefold(k) : k;
			if (c == BRACKET) {
				if (!match_bracket(pat, k, kfold))
					return FNM_NOMATCH;
			} else if (c != QUESTION && k != c && kfold != c) {
				return FNM_NOMATCH;
			}
			pat+=pinc;
			m-=pinc;
			continue;
		}
		break;
	}

	/* Compute real pat length if it was initially unknown/-1 */
	m = strnlen(pat, m);
	endpat = pat + m;

	/* Find the last * in pat and count chars needed after it */
	for (p=ptail=pat; p<endpat; p+=pinc) {
		switch (pat_next(p, endpat-p, &pinc, flags)) {
		case UNMATCHABLE:
			return FNM_NOMATCH;
		case STAR:
			tailcnt=0;
			ptail = p+1;
			break;
		default:
			tailcnt++;
			break;
		}
	}

	/* Past this point we need not check for UNMATCHABLE in pat,
	 * because all of pat has already been parsed once. */

	/* Compute real str length if it was initially unknown/-1 */
	n = strnlen(str, n);
	endstr = str + n;
	if (n < tailcnt) return FNM_NOMATCH;

	/* Find the final tailcnt chars of str, accounting for UTF-8.
	 * On illegal sequences we may get it wrong, but in that case
	 * we necessarily have a matching failure anyway. */
	for (s=endstr; s>str && tailcnt; tailcnt--) {
		if (s[-1] < 128U || MB_CUR_MAX==1) s--;
		else while ((unsigned char)*--s-0x80U<0x40 && s>str);
	}
	if (tailcnt) return FNM_NOMATCH;
	stail = s;

	/* Check that the pat and str tails match */
	p = ptail;
	for (;;) {
		c = pat_next(p, endpat-p, &pinc, flags);
		p += pinc;
		if ((k = str_next(s, endstr-s, &sinc)) <= 0) {
			if (c != END) return FNM_NOMATCH;
			break;
		}
		s += sinc;
		kfold = flags & FNM_CASEFOLD ? casefold(k) : k;
		if (c == BRACKET) {
			if (!match_bracket(p-pinc, k, kfold))
				return FNM_NOMATCH;
		} else if (c != QUESTION && k != c && kfold != c) {
			return FNM_NOMATCH;
		}
	}

	/* We're all done with the tails now, so throw them out */
	endstr = stail;
	endpat = ptail;

	/* Match pattern components until there are none left */
	while (pat<endpat) {
		p = pat;
		s = str;
		for (;;) {
			c = pat_next(p, endpat-p, &pinc, flags);
			p += pinc;
			/* Encountering * completes/commits a component */
			if (c == STAR) {
				pat = p;
				str = s;
				break;
			}
			k = str_next(s, endstr-s, &sinc);
			if (!k)
				return FNM_NOMATCH;
			kfold = flags & FNM_CASEFOLD ? casefold(k) : k;
			if (c == BRACKET) {
				if (!match_bracket(p-pinc, k, kfold))
					break;
			} else if (c != QUESTION && k != c && kfold != c) {
				break;
			}
			s += sinc;
		}
		if (c == STAR) continue;
		/* If we failed, advance str, by 1 char if it's a valid
		 * char, or past all invalid bytes otherwise. */
		k = str_next(str, endstr-str, &sinc);
		if (k > 0) str += sinc;
		else for (str++; str_next(str, endstr-str, &sinc)<0; str++);
	}

	return 0;
}