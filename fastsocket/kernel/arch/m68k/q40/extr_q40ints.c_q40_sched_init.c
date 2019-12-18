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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_CLEAR_REG ; 
 int /*<<< orphan*/  FRAME_RATE_REG ; 
 int Q40_IRQ_FRAME ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  q40_timer_int ; 
 int /*<<< orphan*/  q40_timer_routine ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void q40_sched_init (irq_handler_t timer_routine)
{
	int timer_irq;

	q40_timer_routine = timer_routine;
	timer_irq = Q40_IRQ_FRAME;

	if (request_irq(timer_irq, q40_timer_int, 0,
				"timer", q40_timer_int))
		panic("Couldn't register timer int");

	master_outb(-1, FRAME_CLEAR_REG);
	master_outb( 1, FRAME_RATE_REG);
}