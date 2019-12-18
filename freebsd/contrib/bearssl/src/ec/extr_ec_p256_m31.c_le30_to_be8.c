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

__attribute__((used)) static void
le30_to_be8(unsigned char *dst, size_t len, const uint32_t *src)
{
	uint32_t acc;
	int acc_len;

	acc = 0;
	acc_len = 0;
	while (len -- > 0) {
		if (acc_len < 8) {
			uint32_t w;

			w = *src ++;
			dst[len] = (unsigned char)(acc | (w << acc_len));
			acc = w >> (8 - acc_len);
			acc_len += 22;
		} else {
			dst[len] = (unsigned char)acc;
			acc >>= 8;
			acc_len -= 8;
		}
	}
}