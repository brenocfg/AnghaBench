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
 scalar_t__ COMMAND_REG ; 
 scalar_t__ DEST_BUS_ID ; 
 int ILLEGAL ; 
 scalar_t__ INT_REG ; 
 int NOOP ; 
 int SCI ; 
 scalar_t__ STATUS_REG ; 
 int /*<<< orphan*/  barrier () ; 
 int inb (scalar_t__) ; 
 int jiffies ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int probe_irq_off (int) ; 
 int probe_irq_on () ; 
 int /*<<< orphan*/  sym53c416_init (int,int) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 scalar_t__ time_before_eq (unsigned long,int) ; 

__attribute__((used)) static int sym53c416_probeirq(int base, int scsi_id)
{
	int irq, irqs;
	unsigned long i;

	/* Clear interrupt register */
	inb(base + INT_REG);
	/* Start probing for irq's */
	irqs = probe_irq_on();
	/* Reinit chip */
	sym53c416_init(base, scsi_id);
	/* Cause interrupt */
	outb(NOOP, base + COMMAND_REG);
	outb(ILLEGAL, base + COMMAND_REG);
	outb(0x07, base + DEST_BUS_ID);
	outb(0x00, base + DEST_BUS_ID);
	/* Wait for interrupt to occur */
	i = jiffies + 20;
	while(time_before(jiffies, i) && !(inb(base + STATUS_REG) & SCI))
		barrier();
	if(time_before_eq(i, jiffies))	/* timed out */
		return 0;
	/* Get occurred irq */
	irq = probe_irq_off(irqs);
	sym53c416_init(base, scsi_id);
	return irq;
}