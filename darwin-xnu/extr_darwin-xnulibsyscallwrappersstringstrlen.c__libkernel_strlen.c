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
 uintptr_t LONGPTR_MASK ; 
 unsigned long const mask01 ; 
 unsigned long const mask80 ; 
 int /*<<< orphan*/  testbyte (int) ; 

__attribute__((visibility("hidden")))
size_t
_libkernel_strlen(const char *str)
{
	const char *p;
	const unsigned long *lp;

	/* Skip the first few bytes until we have an aligned p */
	for (p = str; (uintptr_t)p & LONGPTR_MASK; p++)
	    if (*p == '\0')
		return (p - str);

	/* Scan the rest of the string using word sized operation */
	for (lp = (const unsigned long *)p; ; lp++)
	    if ((*lp - mask01) & mask80) {
		p = (const char *)(lp);
		testbyte(0);
		testbyte(1);
		testbyte(2);
		testbyte(3);
#if (LONG_BIT >= 64)
		testbyte(4);
		testbyte(5);
		testbyte(6);
		testbyte(7);
#endif
	    }

	/* NOTREACHED */
	return (0);
}