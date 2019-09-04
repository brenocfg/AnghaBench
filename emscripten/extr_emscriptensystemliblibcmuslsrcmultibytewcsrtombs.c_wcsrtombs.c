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
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t wcrtomb (char*,int const,int /*<<< orphan*/ ) ; 

size_t wcsrtombs(char *restrict s, const wchar_t **restrict ws, size_t n, mbstate_t *restrict st)
{
	const wchar_t *ws2;
	char buf[4];
	size_t N = n, l;
	if (!s) {
		for (n=0, ws2=*ws; *ws2; ws2++) {
			if (*ws2 >= 0x80u) {
				l = wcrtomb(buf, *ws2, 0);
				if (!(l+1)) return -1;
				n += l;
			} else n++;
		}
		return n;
	}
	while (n>=4) {
		if (**ws-1u >= 0x7fu) {
			if (!**ws) {
				*s = 0;
				*ws = 0;
				return N-n;
			}
			l = wcrtomb(s, **ws, 0);
			if (!(l+1)) return -1;
			s += l;
			n -= l;
		} else {
			*s++ = **ws;
			n--;
		}
		(*ws)++;
	}
	while (n) {
		if (**ws-1u >= 0x7fu) {
			if (!**ws) {
				*s = 0;
				*ws = 0;
				return N-n;
			}
			l = wcrtomb(buf, **ws, 0);
			if (!(l+1)) return -1;
			if (l>n) return N-n;
			wcrtomb(s, **ws, 0);
			s += l;
			n -= l;
		} else {
			*s++ = **ws;
			n--;
		}
		(*ws)++;
	}
	return N;
}