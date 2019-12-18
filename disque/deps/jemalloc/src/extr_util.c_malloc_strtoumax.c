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
typedef  unsigned int uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 unsigned int UINTMAX_MAX ; 
 int /*<<< orphan*/  set_errno (int /*<<< orphan*/ ) ; 

uintmax_t
malloc_strtoumax(const char *restrict nptr, char **restrict endptr, int base)
{
	uintmax_t ret, digit;
	unsigned b;
	bool neg;
	const char *p, *ns;

	p = nptr;
	if (base < 0 || base == 1 || base > 36) {
		ns = p;
		set_errno(EINVAL);
		ret = UINTMAX_MAX;
		goto label_return;
	}
	b = base;

	/* Swallow leading whitespace and get sign, if any. */
	neg = false;
	while (true) {
		switch (*p) {
		case '\t': case '\n': case '\v': case '\f': case '\r': case ' ':
			p++;
			break;
		case '-':
			neg = true;
			/* Fall through. */
		case '+':
			p++;
			/* Fall through. */
		default:
			goto label_prefix;
		}
	}

	/* Get prefix, if any. */
	label_prefix:
	/*
	 * Note where the first non-whitespace/sign character is so that it is
	 * possible to tell whether any digits are consumed (e.g., "  0" vs.
	 * "  -x").
	 */
	ns = p;
	if (*p == '0') {
		switch (p[1]) {
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7':
			if (b == 0)
				b = 8;
			if (b == 8)
				p++;
			break;
		case 'X': case 'x':
			switch (p[2]) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f':
				if (b == 0)
					b = 16;
				if (b == 16)
					p += 2;
				break;
			default:
				break;
			}
			break;
		default:
			p++;
			ret = 0;
			goto label_return;
		}
	}
	if (b == 0)
		b = 10;

	/* Convert. */
	ret = 0;
	while ((*p >= '0' && *p <= '9' && (digit = *p - '0') < b)
	    || (*p >= 'A' && *p <= 'Z' && (digit = 10 + *p - 'A') < b)
	    || (*p >= 'a' && *p <= 'z' && (digit = 10 + *p - 'a') < b)) {
		uintmax_t pret = ret;
		ret *= b;
		ret += digit;
		if (ret < pret) {
			/* Overflow. */
			set_errno(ERANGE);
			ret = UINTMAX_MAX;
			goto label_return;
		}
		p++;
	}
	if (neg)
		ret = -ret;

	if (p == ns) {
		/* No conversion performed. */
		set_errno(EINVAL);
		ret = UINTMAX_MAX;
		goto label_return;
	}

label_return:
	if (endptr != NULL) {
		if (p == ns) {
			/* No characters were converted. */
			*endptr = (char *)nptr;
		} else
			*endptr = (char *)p;
	}
	return (ret);
}