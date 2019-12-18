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
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 

int
sclp_service_call(sclp_cmdw_t command, void *sccb)
{
	int cc;

	asm volatile(
		"	.insn	rre,0xb2200000,%1,%2\n"  /* servc %1,%2 */
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=&d" (cc) : "d" (command), "a" (__pa(sccb))
		: "cc", "memory");
	if (cc == 3)
		return -EIO;
	if (cc == 2)
		return -EBUSY;
	return 0;
}