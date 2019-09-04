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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t mbsrtowcs (int /*<<< orphan*/ *,char const**,size_t,int /*<<< orphan*/ *) ; 

size_t mbsnrtowcs(wchar_t *restrict wcs, const char **restrict src, size_t n, size_t wn, mbstate_t *restrict st)
{
	size_t l, cnt=0, n2;
	wchar_t *ws, wbuf[256];
	const char *s = *src;

	if (!wcs) ws = wbuf, wn = sizeof wbuf / sizeof *wbuf;
	else ws = wcs;

	/* making sure output buffer size is at most n/4 will ensure
	 * that mbsrtowcs never reads more than n input bytes. thus
	 * we can use mbsrtowcs as long as it's practical.. */

	while ( s && wn && ( (n2=n/4)>=wn || n2>32 ) ) {
		if (n2>=wn) n2=wn;
		n -= n2;
		l = mbsrtowcs(ws, &s, n2, st);
		if (!(l+1)) {
			cnt = l;
			wn = 0;
			break;
		}
		if (ws != wbuf) {
			ws += l;
			wn -= l;
		}
		cnt += l;
	}
	if (s) while (wn && n) {
		l = mbrtowc(ws, s, n, st);
		if (l+2<=2) {
			if (!(l+1)) {
				cnt = l;
				break;
			}
			if (!l) {
				s = 0;
				break;
			}
			/* have to roll back partial character */
			*(unsigned *)st = 0;
			break;
		}
		s += l; n -= l;
		/* safe - this loop runs fewer than sizeof(wbuf)/8 times */
		ws++; wn--;
		cnt++;
	}
	if (wcs) *src = s;
	return cnt;
}