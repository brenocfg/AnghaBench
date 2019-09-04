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
typedef  size_t wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t CODEUNIT (unsigned char const) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int MB_CUR_MAX ; 
 scalar_t__ OOB (unsigned int,unsigned char const) ; 
 unsigned char const SA ; 
 unsigned char const SB ; 
 unsigned int* bittab ; 
 int /*<<< orphan*/  errno ; 

size_t mbrtowc(wchar_t *restrict wc, const char *restrict src, size_t n, mbstate_t *restrict st)
{
	static unsigned internal_state;
	unsigned c;
	const unsigned char *s = (const void *)src;
	const unsigned N = n;
	wchar_t dummy;

	if (!st) st = (void *)&internal_state;
	c = *(unsigned *)st;
	
	if (!s) {
		if (c) goto ilseq;
		return 0;
	} else if (!wc) wc = &dummy;

	if (!n) return -2;
	if (!c) {
		if (*s < 0x80) return !!(*wc = *s);
		if (MB_CUR_MAX==1) return (*wc = CODEUNIT(*s)), 1;
		if (*s-SA > SB-SA) goto ilseq;
		c = bittab[*s++-SA]; n--;
	}

	if (n) {
		if (OOB(c,*s)) goto ilseq;
loop:
		c = c<<6 | *s++-0x80; n--;
		if (!(c&(1U<<31))) {
			*(unsigned *)st = 0;
			*wc = c;
			return N-n;
		}
		if (n) {
			if (*s-0x80u >= 0x40) goto ilseq;
			goto loop;
		}
	}

	*(unsigned *)st = c;
	return -2;
ilseq:
	*(unsigned *)st = 0;
	errno = EILSEQ;
	return -1;
}