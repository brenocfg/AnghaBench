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

__attribute__((used)) static void encode(unsigned long data, unsigned long *dest)
{
	unsigned long data2;

	data &= 0x55555555;
	data2 = data ^ 0x55555555;
	data |= ((data2 >> 1) | 0x80000000) & (data2 << 1);

	if (*(dest - 1) & 0x00000001)
		data &= 0x7FFFFFFF;

	*dest = data;
}