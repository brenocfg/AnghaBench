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

int
looks_like_DER(const unsigned char *buf, size_t len)
{
	int fb;
	size_t dlen;

	if (len < 2) {
		return 0;
	}
	if (*buf ++ != 0x30) {
		return 0;
	}
	fb = *buf ++;
	len -= 2;
	if (fb < 0x80) {
		return (size_t)fb == len;
	} else if (fb == 0x80) {
		return 0;
	} else {
		fb -= 0x80;
		if (len < (size_t)fb + 2) {
			return 0;
		}
		len -= (size_t)fb;
		dlen = 0;
		while (fb -- > 0) {
			if (dlen > (len >> 8)) {
				return 0;
			}
			dlen = (dlen << 8) + (size_t)*buf ++;
		}
		return dlen == len;
	}
}