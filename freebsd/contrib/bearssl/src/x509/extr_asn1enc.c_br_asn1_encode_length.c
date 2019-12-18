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

size_t
br_asn1_encode_length(void *dest, size_t len)
{
	unsigned char *buf;
	size_t z;
	int i, j;

	buf = dest;
	if (len < 0x80) {
		if (buf != NULL) {
			*buf = len;
		}
		return 1;
	}
	i = 0;
	for (z = len; z != 0; z >>= 8) {
		i ++;
	}
	if (buf != NULL) {
		*buf ++ = 0x80 + i;
		for (j = i - 1; j >= 0; j --) {
			*buf ++ = len >> (j << 3);
		}
	}
	return i + 1;
}