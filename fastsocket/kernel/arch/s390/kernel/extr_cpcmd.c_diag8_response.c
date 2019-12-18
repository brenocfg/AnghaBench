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
typedef  unsigned long addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpcmd_buf ; 

__attribute__((used)) static int diag8_response(int cmdlen, char *response, int *rlen)
{
	register unsigned long reg2 asm ("2") = (addr_t) cpcmd_buf;
	register unsigned long reg3 asm ("3") = (addr_t) response;
	register unsigned long reg4 asm ("4") = cmdlen | 0x40000000L;
	register unsigned long reg5 asm ("5") = *rlen;

	asm volatile(
#ifndef CONFIG_64BIT
		"	diag	%2,%0,0x8\n"
		"	brc	8,1f\n"
		"	ar	%1,%4\n"
#else /* CONFIG_64BIT */
		"	sam31\n"
		"	diag	%2,%0,0x8\n"
		"	sam64\n"
		"	brc	8,1f\n"
		"	agr	%1,%4\n"
#endif /* CONFIG_64BIT */
		"1:\n"
		: "+d" (reg4), "+d" (reg5)
		: "d" (reg2), "d" (reg3), "d" (*rlen) : "cc");
	*rlen = reg5;
	return reg4;
}