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
 int /*<<< orphan*/  MMUCR ; 
 int /*<<< orphan*/  ctrl_barrier () ; 
 unsigned long ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags, status;

	/*
	 * Flush all the TLB.
	 *
	 * Write to the MMU control register's bit:
	 *	TF-bit for SH-3, TI-bit for SH-4.
	 *      It's same position, bit #2.
	 */
	local_irq_save(flags);
	status = ctrl_inl(MMUCR);
	status |= 0x04;
	ctrl_outl(status, MMUCR);
	ctrl_barrier();
	local_irq_restore(flags);
}