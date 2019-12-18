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
typedef  int uint ;

/* Variables and functions */

__attribute__((used)) static uint8_t reverse_bits_8(uint v)
{
	uint r = v; // r will be reversed bits of v; first get LSB of v
	uint s = 8 - 1; // extra shift needed at end

	for (v >>= 1; v; v >>= 1) {
		r <<= 1;
		r |= v & 1;
		s--;
	}

	return r <<= s; // shift when v's highest bits are zero
}