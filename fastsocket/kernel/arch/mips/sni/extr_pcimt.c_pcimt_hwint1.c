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
typedef  int u8 ;

/* Variables and functions */
 int IT_EISA ; 
 int IT_SCSI ; 
 scalar_t__ PCIMT_CSITPEND ; 
 int PCIMT_IRQ_SCSI ; 
 int /*<<< orphan*/  ST0_IM ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int i8259_irq () ; 
 unsigned long read_c0_status () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static void pcimt_hwint1(void)
{
	u8 pend = *(volatile char *)PCIMT_CSITPEND;
	unsigned long flags;

	if (pend & IT_EISA) {
		int irq;
		/*
		 * Note: ASIC PCI's builtin interrupt acknowledge feature is
		 * broken.  Using it may result in loss of some or all i8259
		 * interrupts, so don't use PCIMT_INT_ACKNOWLEDGE ...
		 */
		irq = i8259_irq();
		if (unlikely(irq < 0))
			return;

		do_IRQ(irq);
	}

	if (!(pend & IT_SCSI)) {
		flags = read_c0_status();
		clear_c0_status(ST0_IM);
		do_IRQ(PCIMT_IRQ_SCSI);
		write_c0_status(flags);
	}
}