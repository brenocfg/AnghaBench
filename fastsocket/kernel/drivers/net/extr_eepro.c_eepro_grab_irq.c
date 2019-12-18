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
struct net_device {int base_addr; int irq; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int INT_NO_REG ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  eepro_clear_int (int) ; 
 int /*<<< orphan*/  eepro_diag (int) ; 
 int /*<<< orphan*/  eepro_dis_int (int) ; 
 int /*<<< orphan*/  eepro_dis_intline (int) ; 
 int /*<<< orphan*/  eepro_en_intexec (int) ; 
 int /*<<< orphan*/  eepro_en_intline (int) ; 
 int /*<<< orphan*/  eepro_sw2bank0 (int) ; 
 int /*<<< orphan*/  eepro_sw2bank1 (int) ; 
 int inb (int) ; 
 int* irqrmap ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int probe_irq_off (unsigned long) ; 
 unsigned long probe_irq_on () ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static int	eepro_grab_irq(struct net_device *dev)
{
	int irqlist[] = { 3, 4, 5, 7, 9, 10, 11, 12, 0 };
	int *irqp = irqlist, temp_reg, ioaddr = dev->base_addr;

	eepro_sw2bank1(ioaddr); /* be CAREFUL, BANK 1 now */

	/* Enable the interrupt line. */
	eepro_en_intline(ioaddr);

	/* be CAREFUL, BANK 0 now */
	eepro_sw2bank0(ioaddr);

	/* clear all interrupts */
	eepro_clear_int(ioaddr);

	/* Let EXEC event to interrupt */
	eepro_en_intexec(ioaddr);

	do {
		eepro_sw2bank1(ioaddr); /* be CAREFUL, BANK 1 now */

		temp_reg = inb(ioaddr + INT_NO_REG);
		outb((temp_reg & 0xf8) | irqrmap[*irqp], ioaddr + INT_NO_REG);

		eepro_sw2bank0(ioaddr); /* Switch back to Bank 0 */

		if (request_irq (*irqp, NULL, IRQF_SHARED, "bogus", dev) != EBUSY) {
			unsigned long irq_mask;
			/* Twinkle the interrupt, and check if it's seen */
			irq_mask = probe_irq_on();

			eepro_diag(ioaddr); /* RESET the 82595 */
			mdelay(20);

			if (*irqp == probe_irq_off(irq_mask))  /* It's a good IRQ line */
				break;

			/* clear all interrupts */
			eepro_clear_int(ioaddr);
		}
	} while (*++irqp);

	eepro_sw2bank1(ioaddr); /* Switch back to Bank 1 */

	/* Disable the physical interrupt line. */
	eepro_dis_intline(ioaddr);

	eepro_sw2bank0(ioaddr); /* Switch back to Bank 0 */

	/* Mask all the interrupts. */
	eepro_dis_int(ioaddr);

	/* clear all interrupts */
	eepro_clear_int(ioaddr);

	return dev->irq;
}