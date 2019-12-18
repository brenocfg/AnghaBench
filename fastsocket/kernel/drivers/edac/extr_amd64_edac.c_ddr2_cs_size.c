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

__attribute__((used)) static int ddr2_cs_size(unsigned i, bool dct_width)
{
	unsigned shift = 0;

	if (i <= 2)
		shift = i;
	else if (!(i & 0x1))
		shift = i >> 1;
	else
		shift = (i + 1) >> 1;

	return 128 << (shift + !!dct_width);
}