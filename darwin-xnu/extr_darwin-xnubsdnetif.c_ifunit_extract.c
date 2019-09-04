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
 int /*<<< orphan*/  bcopy (char const*,char*,size_t) ; 
 size_t strlen (char const*) ; 

int
ifunit_extract(const char *src, char *dst, size_t dstlen, int *unit)
{
	const char *cp;
	size_t len, m;
	char c;
	int u;

	if (src == NULL || dst == NULL || dstlen == 0 || unit == NULL)
		return (-1);

	len = strlen(src);
	if (len < 2 || len > dstlen)
		return (-1);
	cp = src + len - 1;
	c = *cp;
	if (c < '0' || c > '9')
		return (-1);		/* trailing garbage */
	u = 0;
	m = 1;
	do {
		if (cp == src)
			return (-1);	/* no interface name */
		u += (c - '0') * m;
		if (u > 1000000)
			return (-1);	/* number is unreasonable */
		m *= 10;
		c = *--cp;
	} while (c >= '0' && c <= '9');
	len = cp - src + 1;
	bcopy(src, dst, len);
	dst[len] = '\0';
	*unit = u;

	return (0);
}