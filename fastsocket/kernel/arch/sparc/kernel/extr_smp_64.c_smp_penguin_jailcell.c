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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_softint (int) ; 
 int /*<<< orphan*/  membar_safe (char*) ; 
 scalar_t__ penguins_are_doing_time ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  prom_world (int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_capture_registry ; 

void smp_penguin_jailcell(int irq, struct pt_regs *regs)
{
	clear_softint(1 << irq);

	preempt_disable();

	__asm__ __volatile__("flushw");
	prom_world(1);
	atomic_inc(&smp_capture_registry);
	membar_safe("#StoreLoad");
	while (penguins_are_doing_time)
		rmb();
	atomic_dec(&smp_capture_registry);
	prom_world(0);

	preempt_enable();
}