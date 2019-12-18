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

__attribute__((used)) static unsigned char swapbits(unsigned char val)
{
	int bit;
	unsigned char res = 0;
	for (bit = 0; bit < 8; bit++) {
		res <<= 1;
		res |= val & 1;
		val >>= 1;
	}
	return res;
}