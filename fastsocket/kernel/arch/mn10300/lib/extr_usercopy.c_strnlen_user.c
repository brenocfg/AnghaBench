#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct TYPE_3__ {scalar_t__ seg; } ;
struct TYPE_4__ {TYPE_1__ addr_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  __addr_ok (char const*) ; 
 TYPE_2__* current_thread_info () ; 

long strnlen_user(const char *s, long n)
{
	unsigned long res, w;

	if (!__addr_ok(s))
		return 0;

	if (n < 0 || n + (u_long) s > current_thread_info()->addr_limit.seg)
		n = current_thread_info()->addr_limit.seg - (u_long)s;

	asm volatile(
		"0:	cmp %4,%0\n"
		"	beq 2f\n"
		"1:	movbu (%0,%3),%1\n"
		"	inc %0\n"
		"	cmp 0,%1\n"
		"	beq 3f\n"
		"	bra 0b\n"
		"2:	clr %0\n"
		"3:\n"
		".section .fixup,\"ax\"\n"
		"4:	jmp 2b\n"
		".previous\n"
		".section __ex_table,\"a\"\n"
		"	.balign 4\n"
		"	.long 1b,4b\n"
		".previous\n"
		:"=d"(res), "=&r"(w)
		:"0"(0), "a"(s), "r"(n)
		:"memory");
	return res;
}