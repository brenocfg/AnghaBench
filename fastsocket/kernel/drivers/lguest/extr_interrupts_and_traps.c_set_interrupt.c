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
struct lg_cpu {int /*<<< orphan*/  tsk; int /*<<< orphan*/  irqs_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  kick_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void set_interrupt(struct lg_cpu *cpu, unsigned int irq)
{
	/*
	 * Next time the Guest runs, the core code will see if it can deliver
	 * this interrupt.
	 */
	set_bit(irq, cpu->irqs_pending);

	/*
	 * Make sure it sees it; it might be asleep (eg. halted), or running
	 * the Guest right now, in which case kick_process() will knock it out.
	 */
	if (!wake_up_process(cpu->tsk))
		kick_process(cpu->tsk);
}