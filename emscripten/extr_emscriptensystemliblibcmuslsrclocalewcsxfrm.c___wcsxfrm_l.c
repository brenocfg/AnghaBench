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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 size_t wcslen (scalar_t__ const*) ; 
 int /*<<< orphan*/  wmemcpy (scalar_t__*,scalar_t__ const*,size_t) ; 

size_t __wcsxfrm_l(wchar_t *restrict dest, const wchar_t *restrict src, size_t n, locale_t loc)
{
	size_t l = wcslen(src);
	if (l < n) {
		wmemcpy(dest, src, l+1);
	} else if (n) {
		wmemcpy(dest, src, n-1);
		dest[n-1] = 0;
	}
	return l;
}