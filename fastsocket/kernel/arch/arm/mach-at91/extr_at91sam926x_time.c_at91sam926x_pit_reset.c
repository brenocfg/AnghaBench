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
 int /*<<< orphan*/  AT91_PIT_MR ; 
 int AT91_PIT_PITEN ; 
 int /*<<< orphan*/  AT91_PIT_PIVR ; 
 scalar_t__ PIT_CPIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int pit_cycle ; 

__attribute__((used)) static void at91sam926x_pit_reset(void)
{
	/* Disable timer and irqs */
	at91_sys_write(AT91_PIT_MR, 0);

	/* Clear any pending interrupts, wait for PIT to stop counting */
	while (PIT_CPIV(at91_sys_read(AT91_PIT_PIVR)) != 0)
		cpu_relax();

	/* Start PIT but don't enable IRQ */
	at91_sys_write(AT91_PIT_MR, (pit_cycle - 1) | AT91_PIT_PITEN);
}