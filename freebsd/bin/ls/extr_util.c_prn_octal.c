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
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 scalar_t__ UCHAR_MAX ; 
 scalar_t__ f_octal_escape ; 
 scalar_t__ iswprint (int) ; 
 size_t mbrtowc (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ wcwidth (int) ; 

int
prn_octal(const char *s)
{
	static const char esc[] = "\\\\\"\"\aa\bb\ff\nn\rr\tt\vv";
	const char *p;
	mbstate_t mbs;
	wchar_t wc;
	size_t clen;
	unsigned char ch;
	int goodchar, i, len, prtlen;

	memset(&mbs, 0, sizeof(mbs));
	len = 0;
	while ((clen = mbrtowc(&wc, s, MB_LEN_MAX, &mbs)) != 0) {
		goodchar = clen != (size_t)-1 && clen != (size_t)-2;
		if (goodchar && iswprint(wc) && wc != L'\"' && wc != L'\\') {
			for (i = 0; i < (int)clen; i++)
				putchar((unsigned char)s[i]);
			len += wcwidth(wc);
		} else if (goodchar && f_octal_escape &&
#if WCHAR_MIN < 0
                    wc >= 0 &&
#endif
		    wc <= (wchar_t)UCHAR_MAX &&
		    (p = strchr(esc, (char)wc)) != NULL) {
			putchar('\\');
			putchar(p[1]);
			len += 2;
		} else {
			if (goodchar)
				prtlen = clen;
			else if (clen == (size_t)-1)
				prtlen = 1;
			else
				prtlen = strlen(s);
			for (i = 0; i < prtlen; i++) {
				ch = (unsigned char)s[i];
				putchar('\\');
				putchar('0' + (ch >> 6));
				putchar('0' + ((ch >> 3) & 7));
				putchar('0' + (ch & 7));
				len += 4;
			}
		}
		if (clen == (size_t)-2)
			break;
		if (clen == (size_t)-1) {
			memset(&mbs, 0, sizeof(mbs));
			s++;
		} else
			s += clen;
	}
	return (len);
}