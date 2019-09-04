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

int __dn_expand(const unsigned char *base, const unsigned char *end, const unsigned char *src, char *dest, int space)
{
	const unsigned char *p = src;
	char *dend, *dbegin = dest;
	int len = -1, i, j;
	if (p==end || space <= 0) return -1;
	dend = dest + (space > 254 ? 254 : space);
	/* detect reference loop using an iteration counter */
	for (i=0; i < end-base; i+=2) {
		/* loop invariants: p<end, dest<dend */
		if (*p & 0xc0) {
			if (p+1==end) return -1;
			j = ((p[0] & 0x3f) << 8) | p[1];
			if (len < 0) len = p+2-src;
			if (j >= end-base) return -1;
			p = base+j;
		} else if (*p) {
			if (dest != dbegin) *dest++ = '.';
			j = *p++;
			if (j >= end-p || j >= dend-dest) return -1;
			while (j--) *dest++ = *p++;
		} else {
			*dest = 0;
			if (len < 0) len = p+1-src;
			return len;
		}
	}
	return -1;
}