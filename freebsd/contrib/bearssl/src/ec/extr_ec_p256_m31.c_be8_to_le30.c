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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
be8_to_le30(uint32_t *dst, const unsigned char *src, size_t len)
{
	uint32_t acc;
	int acc_len;

	acc = 0;
	acc_len = 0;
	while (len -- > 0) {
		uint32_t b;

		b = src[len];
		if (acc_len < 22) {
			acc |= b << acc_len;
			acc_len += 8;
		} else {
			*dst ++ = (acc | (b << acc_len)) & 0x3FFFFFFF;
			acc = b >> (30 - acc_len);
			acc_len -= 22;
		}
	}
	return acc;
}