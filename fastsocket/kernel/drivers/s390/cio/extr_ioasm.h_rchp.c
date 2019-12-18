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
struct chp_id {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int rchp(struct chp_id chpid)
{
	register struct chp_id reg1 asm ("1") = chpid;
	int ccode;

	asm volatile(
		"	lr	1,%1\n"
		"	rchp\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode) : "d" (reg1) : "cc");
	return ccode;
}