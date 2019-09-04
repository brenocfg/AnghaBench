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
 int BRACKET ; 
 int END ; 
 int FNM_NOESCAPE ; 
 int QUESTION ; 
 int STAR ; 
 int UNMATCHABLE ; 
 int mbtowc (int*,char const*,size_t) ; 

__attribute__((used)) static int pat_next(const char *pat, size_t m, size_t *step, int flags)
{
	int esc = 0;
	if (!m || !*pat) {
		*step = 0;
		return END;
	}
	*step = 1;
	if (pat[0]=='\\' && pat[1] && !(flags & FNM_NOESCAPE)) {
		*step = 2;
		pat++;
		esc = 1;
		goto escaped;
	}
	if (pat[0]=='[') {
		size_t k = 1;
		if (k<m) if (pat[k] == '^' || pat[k] == '!') k++;
		if (k<m) if (pat[k] == ']') k++;
		for (; k<m && pat[k] && pat[k]!=']'; k++) {
			if (k+1<m && pat[k+1] && pat[k]=='[' && (pat[k+1]==':' || pat[k+1]=='.' || pat[k+1]=='=')) {
				int z = pat[k+1];
				k+=2;
				if (k<m && pat[k]) k++;
				while (k<m && pat[k] && (pat[k-1]!=z || pat[k]!=']')) k++;
				if (k==m || !pat[k]) break;
			}
		}
		if (k==m || !pat[k]) {
			*step = 1;
			return '[';
		}
		*step = k+1;
		return BRACKET;
	}
	if (pat[0] == '*')
		return STAR;
	if (pat[0] == '?')
		return QUESTION;
escaped:
	if (pat[0] >= 128U) {
		wchar_t wc;
		int k = mbtowc(&wc, pat, m);
		if (k<0) {
			*step = 0;
			return UNMATCHABLE;
		}
		*step = k + esc;
		return wc;
	}
	return pat[0];
}