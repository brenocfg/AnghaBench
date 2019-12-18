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
typedef  int ssize_t ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char const*) ; 

ssize_t
blhexdump(char *buf, size_t len, const char *str, const void *b, size_t l)
{
	size_t z, cz;
	int r;
	const unsigned char *p = b;
	const unsigned char *e = p + l;

	r = snprintf(buf, len, "%s: ", str);
	if (r == -1)
		return -1;
	if ((cz = z = (size_t)r) >= len)
		cz = len;

	while (p < e) {
		r = snprintf(buf + cz, len - cz, "%.2x", *p++);
		if (r == -1)
			return -1;
		if ((cz = (z += (size_t)r)) >= len)
			cz = len;
	}
	return (ssize_t)z;
}