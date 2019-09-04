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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 scalar_t__ iswctype (int,int /*<<< orphan*/ ) ; 
 int mbtowc (scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  wctype (char*) ; 

__attribute__((used)) static int match_bracket(const char *p, int k, int kfold)
{
	wchar_t wc;
	int inv = 0;
	p++;
	if (*p=='^' || *p=='!') {
		inv = 1;
		p++;
	}
	if (*p==']') {
		if (k==']') return !inv;
		p++;
	} else if (*p=='-') {
		if (k=='-') return !inv;
		p++;
	}
	wc = p[-1];
	for (; *p != ']'; p++) {
		if (p[0]=='-' && p[1]!=']') {
			wchar_t wc2;
			int l = mbtowc(&wc2, p+1, 4);
			if (l < 0) return 0;
			if (wc <= wc2)
				if ((unsigned)k-wc <= wc2-wc ||
				    (unsigned)kfold-wc <= wc2-wc)
					return !inv;
			p += l-1;
			continue;
		}
		if (p[0]=='[' && (p[1]==':' || p[1]=='.' || p[1]=='=')) {
			const char *p0 = p+2;
			int z = p[1];
			p+=3;
			while (p[-1]!=z || p[0]!=']') p++;
			if (z == ':' && p-1-p0 < 16) {
				char buf[16];
				memcpy(buf, p0, p-1-p0);
				buf[p-1-p0] = 0;
				if (iswctype(k, wctype(buf)) ||
				    iswctype(kfold, wctype(buf)))
					return !inv;
			}
			continue;
		}
		if (*p < 128U) {
			wc = (unsigned char)*p;
		} else {
			int l = mbtowc(&wc, p, 4);
			if (l < 0) return 0;
			p += l-1;
		}
		if (wc==k || wc==kfold) return !inv;
	}
	return inv;
}