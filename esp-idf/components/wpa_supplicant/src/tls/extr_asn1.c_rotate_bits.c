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

__attribute__((used)) static u8 rotate_bits(u8 octet)
{
	int i;
	u8 res;

	res = 0;
	for (i = 0; i < 8; i++) {
		res <<= 1;
		if (octet & 1)
			res |= 1;
		octet >>= 1;
	}

	return res;
}