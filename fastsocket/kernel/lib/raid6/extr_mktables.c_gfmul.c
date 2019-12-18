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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t gfmul(uint8_t a, uint8_t b)
{
	uint8_t v = 0;

	while (b) {
		if (b & 1)
			v ^= a;
		a = (a << 1) ^ (a & 0x80 ? 0x1d : 0);
		b >>= 1;
	}

	return v;
}