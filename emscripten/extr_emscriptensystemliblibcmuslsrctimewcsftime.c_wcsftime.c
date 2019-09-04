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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 size_t __wcsftime_l (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,struct tm const*,int /*<<< orphan*/ ) ; 

size_t wcsftime(wchar_t *restrict wcs, size_t n, const wchar_t *restrict f, const struct tm *restrict tm)
{
	return __wcsftime_l(wcs, n, f, tm, CURRENT_LOCALE);
}