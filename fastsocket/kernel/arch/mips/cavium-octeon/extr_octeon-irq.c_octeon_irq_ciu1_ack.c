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
 int /*<<< orphan*/  clear_c0_status (int) ; 

__attribute__((used)) static void octeon_irq_ciu1_ack(unsigned int irq)
{
	/*
	 * In order to avoid any locking accessing the CIU, we
	 * acknowledge CIU interrupts by disabling all of them.  This
	 * way we can use a per core register and avoid any out of
	 * core locking requirements.  This has the side affect that
	 * CIU interrupts can't be processed recursively.  We don't
	 * need to disable IRQs to make these atomic since they are
	 * already disabled earlier in the low level interrupt code.
	 */
	clear_c0_status(0x100 << 3);
}