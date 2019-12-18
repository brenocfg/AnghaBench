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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static inline int sca3000_11bit_convert(uint8_t msb, uint8_t lsb)
{
	int16_t val;

	val = ((lsb >> 3) & 0x1C) | (msb << 5);
	val |= (val & (1 << 12)) ? 0xE000 : 0;

	return val;
}