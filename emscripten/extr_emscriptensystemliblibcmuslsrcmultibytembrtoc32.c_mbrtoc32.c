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
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 

size_t mbrtoc32(char32_t *restrict pc32, const char *restrict s, size_t n, mbstate_t *restrict ps)
{
	static unsigned internal_state;
	if (!ps) ps = (void *)&internal_state;
	if (!s) return mbrtoc32(0, "", 1, ps);
	wchar_t wc;
	size_t ret = mbrtowc(&wc, s, n, ps);
	if (ret <= 4 && pc32) *pc32 = wc;
	return ret;
}