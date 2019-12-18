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

__attribute__((used)) static inline unsigned long do_clear_global_summary(void)
{
	register unsigned long __fn asm("1") = 3;
	register unsigned long __tmp asm("2");
	register unsigned long __time asm("3");

	asm volatile(
		"	.insn	rre,0xb2650000,2,0"
		: "+d" (__fn), "=d" (__tmp), "=d" (__time));
	return __time;
}