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
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 

__attribute__((used)) static void rm7k_wait_irqoff(void)
{
	local_irq_disable();
	if (!need_resched())
		__asm__(
		"	.set	push					\n"
		"	.set	mips3					\n"
		"	.set	noat					\n"
		"	mfc0	$1, $12					\n"
		"	sync						\n"
		"	mtc0	$1, $12		# stalls until W stage	\n"
		"	wait						\n"
		"	mtc0	$1, $12		# stalls until W stage	\n"
		"	.set	pop					\n");
	local_irq_enable();
}