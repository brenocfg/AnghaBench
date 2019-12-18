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

/* Variables and functions */
 unsigned int KSTRTOX_OVERFLOW ; 
 scalar_t__ ULLONG_MAX ; 
 char _tolower (char const) ; 
 unsigned long long div_u64 (scalar_t__,unsigned int) ; 
 scalar_t__ unlikely (unsigned long long) ; 

unsigned int _parse_integer(const char *s, unsigned int base, unsigned long long *p)
{
	unsigned long long res;
	unsigned int rv;
	int overflow;

	res = 0;
	rv = 0;
	overflow = 0;
	while (*s) {
		unsigned int val;

		if ('0' <= *s && *s <= '9')
			val = *s - '0';
		else if ('a' <= _tolower(*s) && _tolower(*s) <= 'f')
			val = _tolower(*s) - 'a' + 10;
		else
			break;

		if (val >= base)
			break;
		/*
		 * Check for overflow only if we are within range of
		 * it in the max base we support (16)
		 */
		if (unlikely(res & (~0ull << 60))) {
			if (res > div_u64(ULLONG_MAX - val, base))
				overflow = 1;
		}
		res = res * base + val;
		rv++;
		s++;
	}
	*p = res;
	if (overflow)
		rv |= KSTRTOX_OVERFLOW;
	return rv;
}