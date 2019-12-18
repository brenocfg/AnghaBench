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
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 scalar_t__ iswprint (int /*<<< orphan*/ ) ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (unsigned char) ; 
 scalar_t__ wcwidth (int /*<<< orphan*/ ) ; 

int
prn_normal(const char *s)
{
	mbstate_t mbs;
	wchar_t wc;
	int i, n;
	size_t clen;

	memset(&mbs, 0, sizeof(mbs));
	n = 0;
	while ((clen = mbrtowc(&wc, s, MB_LEN_MAX, &mbs)) != 0) {
		if (clen == (size_t)-2) {
			n += printf("%s", s);
			break;
		}
		if (clen == (size_t)-1) {
			memset(&mbs, 0, sizeof(mbs));
			putchar((unsigned char)*s);
			s++;
			n++;
			continue;
		}
		for (i = 0; i < (int)clen; i++)
			putchar((unsigned char)s[i]);
		s += clen;
		if (iswprint(wc))
			n += wcwidth(wc);
	}
	return (n);
}