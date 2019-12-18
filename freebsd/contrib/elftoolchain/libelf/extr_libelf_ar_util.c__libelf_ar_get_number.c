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
 int /*<<< orphan*/  assert (int) ; 

int
_libelf_ar_get_number(const char *src, size_t sz, unsigned int base,
    size_t *ret)
{
	size_t r;
	unsigned int c, v;
	const unsigned char *e, *s;

	assert(base <= 10);

	s = (const unsigned char *) src;
	e = s + sz;

	/* skip leading blanks */
	for (;s < e && (c = *s) == ' '; s++)
		;

	r = 0L;
	for (;s < e; s++) {
		if ((c = *s) == ' ')
			break;
		if (c < '0' || c > '9')
			return (0);
		v = c - '0';
		if (v >= base)		/* Illegal digit. */
			break;
		r *= base;
		r += v;
	}

	*ret = r;

	return (1);
}