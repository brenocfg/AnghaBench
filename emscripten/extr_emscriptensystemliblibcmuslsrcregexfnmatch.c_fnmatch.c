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
 int END ; 
 int FNM_LEADING_DIR ; 
 int FNM_NOMATCH ; 
 int FNM_PATHNAME ; 
 int fnmatch_internal (char const*,int,char const*,int,int) ; 
 int pat_next (char const*,int,size_t*,int) ; 

int fnmatch(const char *pat, const char *str, int flags)
{
	const char *s, *p;
	size_t inc;
	int c;
	if (flags & FNM_PATHNAME) for (;;) {
		for (s=str; *s && *s!='/'; s++);
		for (p=pat; (c=pat_next(p, -1, &inc, flags))!=END && c!='/'; p+=inc);
		if (c!=*s && (!*s || !(flags & FNM_LEADING_DIR)))
			return FNM_NOMATCH;
		if (fnmatch_internal(pat, p-pat, str, s-str, flags))
			return FNM_NOMATCH;
		if (!c) return 0;
		str = s+1;
		pat = p+inc;
	} else if (flags & FNM_LEADING_DIR) {
		for (s=str; *s; s++) {
			if (*s != '/') continue;
			if (!fnmatch_internal(pat, -1, str, s-str, flags))
				return 0;
		}
	}
	return fnmatch_internal(pat, -1, str, -1, flags);
}