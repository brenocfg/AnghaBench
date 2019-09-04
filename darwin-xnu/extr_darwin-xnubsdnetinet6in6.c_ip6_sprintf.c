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
typedef  scalar_t__ u_short ;
typedef  int u_char ;
struct in6_addr {int dummy; } ;

/* Variables and functions */

char *
ip6_sprintf(const struct in6_addr *addr)
{
	static const char digits[] = "0123456789abcdef";
	static int ip6round = 0;
	static char ip6buf[8][48];

	int i;
	char *cp;
	const u_short *a = (const u_short *)addr;
	const u_char *d;
	u_char n;
	int dcolon = 0;
	int zpad = 0;

	ip6round = (ip6round + 1) & 7;
	cp = ip6buf[ip6round];

	for (i = 0; i < 8; i++) {
		if (dcolon == 1) {
			if (*a == 0) {
				if (i == 7)
					*cp++ = ':';
				a++;
				continue;
			} else
				dcolon = 2;
		}
		if (*a == 0) {
			if (dcolon == 0 && *(a + 1) == 0) {
				if (i == 0)
					*cp++ = ':';
				*cp++ = ':';
				dcolon = 1;
			} else {
				*cp++ = '0';
				*cp++ = ':';
			}
			a++;
			continue;
		}
		d = (const u_char *)a;
		zpad = 0;
		if ((n = *d >> 4) != 0) {
			*cp++ = digits[n];
			zpad = 1;
		}
		if ((n = *d++ & 0xf) != 0 || zpad) {
			*cp++ = digits[n];
			zpad = 1;
		}
		if ((n = *d >> 4) != 0 || zpad) {
			*cp++ = digits[n];
			zpad = 1;
		}
		if ((n = *d & 0xf) != 0 || zpad)
			*cp++ = digits[n];
		*cp++ = ':';
		a++;
	}
	*--cp = 0;
	return (ip6buf[ip6round]);
}