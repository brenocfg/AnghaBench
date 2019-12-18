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
typedef  unsigned long ulong ;

/* Variables and functions */

__attribute__((used)) static unsigned long decode (unsigned long *data, unsigned long *raw,
			     int len)
{
	ulong *odd, *even;

	/* convert length from bytes to longwords */
	len >>= 2;
	odd = raw;
	even = odd + len;

	/* prepare return pointer */
	raw += len * 2;

	do {
		*data++ = ((*odd++ & 0x55555555) << 1) | (*even++ & 0x55555555);
	} while (--len != 0);

	return (ulong)raw;
}