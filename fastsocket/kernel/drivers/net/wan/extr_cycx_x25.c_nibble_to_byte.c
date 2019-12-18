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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static void nibble_to_byte(u8 *s, u8 *d, u8 len, u8 nibble)
{
	if (nibble) {
		*d++ = '0' + (*s++ & 0x0F);
		--len;
	}

	while (len) {
		*d++ = '0' + (*s >> 4);

		if (--len) {
			*d++ = '0' + (*s & 0x0F);
			--len;
		} else break;

		++s;
	}

	*d = '\0';
}