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
 int CHIP_RESET ; 
 int /*<<< orphan*/  CMD_REG ; 
 int /*<<< orphan*/  INT_REG ; 
 int /*<<< orphan*/  REG0 ; 
 int SCSI_NOP ; 
 int /*<<< orphan*/  STAT_REG ; 
 unsigned long WATCHDOG ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  chip_init () ; 
 int inb (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int probe_irq_off (int) ; 
 int probe_irq_on () ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int irq_probe(void)
{
	int irqs, irq;
	unsigned long i;

	inb(INT_REG);		/* clear the interrupt register */
	irqs = probe_irq_on();

	/* Invalid command will cause an interrupt */
	REG0;
	outb(0xff, CMD_REG);

	/* Wait for the interrupt to occur */
	i = jiffies + WATCHDOG;
	while (time_after(i, jiffies) && !(inb(STAT_REG) & 0x80))
		barrier();
	if (time_before_eq(i, jiffies)) {	/* Timed out, must be hardware trouble */
		probe_irq_off(irqs);
		return -1;
	}

	irq = probe_irq_off(irqs);

	/* Kick the chip */
	outb(CHIP_RESET, CMD_REG);
	outb(SCSI_NOP, CMD_REG);
	chip_init();

	return irq;
}