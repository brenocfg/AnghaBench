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

int strcmp(const char *cs, const char *ct)
{
	register int r0 asm("0") = 0;
	int ret = 0;

	asm volatile ("0: clst %2,%3\n"
		      "   jo   0b\n"
		      "   je   1f\n"
		      "   ic   %0,0(%2)\n"
		      "   ic   %1,0(%3)\n"
		      "   sr   %0,%1\n"
		      "1:"
		      : "+d" (ret), "+d" (r0), "+a" (cs), "+a" (ct)
		      : : "cc" );
	return ret;
}