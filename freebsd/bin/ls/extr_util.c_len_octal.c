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
 scalar_t__ iswprint (int /*<<< orphan*/ ) ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

size_t
len_octal(const char *s, int len)
{
	mbstate_t mbs;
	wchar_t wc;
	size_t clen, r;

	memset(&mbs, 0, sizeof(mbs));
	r = 0;
	while (len != 0 && (clen = mbrtowc(&wc, s, len, &mbs)) != 0) {
		if (clen == (size_t)-1) {
			r += 4;
			s++;
			len--;
			memset(&mbs, 0, sizeof(mbs));
			continue;
		}
		if (clen == (size_t)-2) {
			r += 4 * len;
			break;
		}
		if (iswprint(wc))
			r++;
		else
			r += 4 * clen;
		s += clen;
	}
	return (r);
}