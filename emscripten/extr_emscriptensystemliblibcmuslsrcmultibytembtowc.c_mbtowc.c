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
 int CODEUNIT (unsigned char const) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int MB_CUR_MAX ; 
 scalar_t__ OOB (unsigned int,unsigned char const) ; 
 unsigned char const SA ; 
 unsigned char const SB ; 
 unsigned int* bittab ; 
 int /*<<< orphan*/  errno ; 

int mbtowc(wchar_t *restrict wc, const char *restrict src, size_t n)
{
	unsigned c;
	const unsigned char *s = (const void *)src;
	wchar_t dummy;

	if (!s) return 0;
	if (!n) goto ilseq;
	if (!wc) wc = &dummy;

	if (*s < 0x80) return !!(*wc = *s);
	if (MB_CUR_MAX==1) return (*wc = CODEUNIT(*s)), 1;
	if (*s-SA > SB-SA) goto ilseq;
	c = bittab[*s++-SA];

	/* Avoid excessive checks against n: If shifting the state n-1
	 * times does not clear the high bit, then the value of n is
	 * insufficient to read a character */
	if (n<4 && ((c<<(6*n-6)) & (1U<<31))) goto ilseq;

	if (OOB(c,*s)) goto ilseq;
	c = c<<6 | *s++-0x80;
	if (!(c&(1U<<31))) {
		*wc = c;
		return 2;
	}

	if (*s-0x80u >= 0x40) goto ilseq;
	c = c<<6 | *s++-0x80;
	if (!(c&(1U<<31))) {
		*wc = c;
		return 3;
	}

	if (*s-0x80u >= 0x40) goto ilseq;
	*wc = c<<6 | *s++-0x80;
	return 4;

ilseq:
	errno = EILSEQ;
	return -1;
}