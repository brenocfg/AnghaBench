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

/* Variables and functions */
 int /*<<< orphan*/ * twoway_wcsstr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

wchar_t *wcsstr(const wchar_t *restrict h, const wchar_t *restrict n)
{
	/* Return immediately on empty needle or haystack */
	if (!n[0]) return (wchar_t *)h;
	if (!h[0]) return 0;

	/* Use faster algorithms for short needles */
	h = wcschr(h, *n);
	if (!h || !n[1]) return (wchar_t *)h;
	if (!h[1]) return 0;

	return twoway_wcsstr(h, n);
}