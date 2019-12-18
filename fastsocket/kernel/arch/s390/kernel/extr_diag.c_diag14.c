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

int diag14(unsigned long rx, unsigned long ry1, unsigned long subcode)
{
	register unsigned long _ry1 asm("2") = ry1;
	register unsigned long _ry2 asm("3") = subcode;
	int rc = 0;

	asm volatile(
#ifdef CONFIG_64BIT
		"   sam31\n"
		"   diag    %2,2,0x14\n"
		"   sam64\n"
#else
		"   diag    %2,2,0x14\n"
#endif
		"   ipm     %0\n"
		"   srl     %0,28\n"
		: "=d" (rc), "+d" (_ry2)
		: "d" (rx), "d" (_ry1)
		: "cc");

	return rc;
}