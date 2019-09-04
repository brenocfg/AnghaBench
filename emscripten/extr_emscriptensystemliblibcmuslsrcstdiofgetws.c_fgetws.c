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
typedef  char wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ *) ; 
 char WEOF ; 
 char __fgetwc_unlocked (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 

wchar_t *fgetws(wchar_t *restrict s, int n, FILE *restrict f)
{
	wchar_t *p = s;

	if (!n--) return s;

	FLOCK(f);

	for (; n; n--) {
		wint_t c = __fgetwc_unlocked(f);
		if (c == WEOF) break;
		*p++ = c;
		if (c == '\n') break;
	}
	*p = 0;
	if (ferror(f)) p = s;

	FUNLOCK(f);

	return (p == s) ? NULL : s;
}