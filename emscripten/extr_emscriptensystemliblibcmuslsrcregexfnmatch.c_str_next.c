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
 int mbtowc (int*,char const*,size_t) ; 

__attribute__((used)) static int str_next(const char *str, size_t n, size_t *step)
{
	if (!n) {
		*step = 0;
		return 0;
	}
	if (str[0] >= 128U) {
		wchar_t wc;
		int k = mbtowc(&wc, str, n);
		if (k<0) {
			*step = 1;
			return -1;
		}
		*step = k;
		return wc;
	}
	*step = 1;
	return str[0];
}