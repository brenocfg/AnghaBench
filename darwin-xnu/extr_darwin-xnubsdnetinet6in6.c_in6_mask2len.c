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
typedef  int u_char ;
struct in6_addr {int dummy; } ;

/* Variables and functions */

int
in6_mask2len(struct in6_addr *mask, u_char *lim0)
{
	int x = 0, y;
	u_char *lim = lim0, *p;

	/* ignore the scope_id part */
	if (lim0 == NULL || lim0 - (u_char *)mask > sizeof (*mask))
		lim = (u_char *)mask + sizeof (*mask);
	for (p = (u_char *)mask; p < lim; x++, p++) {
		if (*p != 0xff)
			break;
	}
	y = 0;
	if (p < lim) {
		for (y = 0; y < 8; y++) {
			if ((*p & (0x80 >> y)) == 0)
				break;
		}
	}

	/*
	 * when the limit pointer is given, do a stricter check on the
	 * remaining bits.
	 */
	if (p < lim) {
		if (y != 0 && (*p & (0x00ff >> y)) != 0)
			return (-1);
		for (p = p + 1; p < lim; p++)
			if (*p != 0)
				return (-1);
	}

	return (x * 8 + y);
}