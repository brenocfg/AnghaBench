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
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  IS_CODEUNIT (int) ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  errno ; 

size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict st)
{
	if (!s) return 1;
	if ((unsigned)wc < 0x80) {
		*s = wc;
		return 1;
	} else if (MB_CUR_MAX == 1) {
		if (!IS_CODEUNIT(wc)) {
			errno = EILSEQ;
			return -1;
		}
		*s = wc;
		return 1;
	} else if ((unsigned)wc < 0x800) {
		*s++ = 0xc0 | (wc>>6);
		*s = 0x80 | (wc&0x3f);
		return 2;
	} else if ((unsigned)wc < 0xd800 || (unsigned)wc-0xe000 < 0x2000) {
		*s++ = 0xe0 | (wc>>12);
		*s++ = 0x80 | ((wc>>6)&0x3f);
		*s = 0x80 | (wc&0x3f);
		return 3;
	} else if ((unsigned)wc-0x10000 < 0x100000) {
		*s++ = 0xf0 | (wc>>18);
		*s++ = 0x80 | ((wc>>12)&0x3f);
		*s++ = 0x80 | ((wc>>6)&0x3f);
		*s = 0x80 | (wc&0x3f);
		return 4;
	}
	errno = EILSEQ;
	return -1;
}