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
 size_t wcrtomb (char*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 size_t wcsrtombs (char*,int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/ ) ; 

size_t wcsnrtombs(char *restrict dst, const wchar_t **restrict wcs, size_t wn, size_t n, mbstate_t *restrict st)
{
	size_t l, cnt=0, n2;
	char *s, buf[256];
	const wchar_t *ws = *wcs;

	if (!dst) s = buf, n = sizeof buf;
	else s = dst;

	while ( ws && n && ( (n2=wn)>=n || n2>32 ) ) {
		if (n2>=n) n2=n;
		wn -= n2;
		l = wcsrtombs(s, &ws, n2, 0);
		if (!(l+1)) {
			cnt = l;
			n = 0;
			break;
		}
		if (s != buf) {
			s += l;
			n -= l;
		}
		cnt += l;
	}
	if (ws) while (n && wn) {
		l = wcrtomb(s, *ws, 0);
		if ((l+1)<=1) {
			if (!l) ws = 0;
			else cnt = l;
			break;
		}
		ws++; wn--;
		/* safe - this loop runs fewer than sizeof(buf) times */
		s+=l; n-=l;
		cnt += l;
	}
	if (dst) *wcs = ws;
	return cnt;
}