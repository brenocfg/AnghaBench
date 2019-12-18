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
 char* __builtin_strcpy (char*,char const*) ; 

char *strcpy(char *dest, const char *src)
{
#if __GNUC__ < 4
	register int r0 asm("0") = 0;
	char *ret = dest;

	asm volatile ("0: mvst  %0,%1\n"
		      "   jo    0b"
		      : "+&a" (dest), "+&a" (src) : "d" (r0)
		      : "cc", "memory" );
	return ret;
#else
	return __builtin_strcpy(dest, src);
#endif
}