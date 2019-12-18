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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int hexval (int) ; 
 int /*<<< orphan*/  stderr ; 

size_t
parse_size(const char *s)
{
	int radix;
	size_t acc;
	const char *t;

	t = s;
	if (t[0] == '0' && (t[1] == 'x' || t[1] == 'X')) {
		radix = 16;
		t += 2;
	} else {
		radix = 10;
	}
	acc = 0;
	for (;;) {
		int c, d;
		size_t z;

		c = *t ++;
		if (c == 0) {
			return acc;
		}
		d = hexval(c);
		if (d < 0 || d >= radix) {
			fprintf(stderr, "ERROR: not a valid digit: '%c'\n", c);
			return (size_t)-1;
		}
		z = acc * (size_t)radix + (size_t)d;
		if (z < (size_t)d || (z / (size_t)radix) != acc
			|| z == (size_t)-1)
		{
			fprintf(stderr, "ERROR: value too large: %s\n", s);
			return (size_t)-1;
		}
		acc = z;
	}
}