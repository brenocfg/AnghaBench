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
typedef  int uint ;

/* Variables and functions */
 int CPU_INT_LEVEL ; 
 int /*<<< orphan*/  m68ki_check_interrupts () ; 
 int /*<<< orphan*/  m68ki_exception_interrupt (int) ; 

void m68k_set_irq(unsigned int int_level)
{
	uint old_level = CPU_INT_LEVEL;
	CPU_INT_LEVEL = int_level << 8;

	/* A transition from < 7 to 7 always interrupts (NMI) */
	/* Note: Level 7 can also level trigger like a normal IRQ */
	if(old_level != 0x0700 && CPU_INT_LEVEL == 0x0700)
		m68ki_exception_interrupt(7); /* Edge triggered level 7 (NMI) */
	else
		m68ki_check_interrupts(); /* Level triggered (IRQ) */
}