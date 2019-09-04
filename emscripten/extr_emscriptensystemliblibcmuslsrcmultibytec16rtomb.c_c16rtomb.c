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
typedef  int char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  errno ; 
 size_t wcrtomb (char*,int,int /*<<< orphan*/ ) ; 

size_t c16rtomb(char *restrict s, char16_t c16, mbstate_t *restrict ps)
{
	static unsigned internal_state;
	if (!ps) ps = (void *)&internal_state;
	unsigned *x = (unsigned *)ps;
	wchar_t wc;

	if (!s) {
		if (*x) goto ilseq;
		return 1;
	}

	if (!*x && c16 - 0xd800u < 0x400) {
		*x = c16 - 0xd7c0 << 10;
		return 0;
	}

	if (*x) {
		if (c16 - 0xdc00u >= 0x400) goto ilseq;
		else wc = *x + c16 - 0xdc00;
		*x = 0;
	} else {
		wc = c16;
	}
	return wcrtomb(s, wc, 0);

ilseq:
	*x = 0;
	errno = EILSEQ;
	return -1;
}