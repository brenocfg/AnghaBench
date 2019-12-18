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
struct sys_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_VALID ; 
 unsigned int IRQ_S3C2440_AC97 ; 
 unsigned int IRQ_S3C2440_WDT ; 
 unsigned int IRQ_WDT ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  s3c_irq_demux_wdtac97 ; 
 int /*<<< orphan*/  s3c_irq_level_chip ; 
 int /*<<< orphan*/  s3c_irq_wdtac97 ; 
 int /*<<< orphan*/  set_irq_chained_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2440_irq_add(struct sys_device *sysdev)
{
	unsigned int irqno;

	printk("S3C2440: IRQ Support\n");

	/* add new chained handler for wdt, ac7 */

	set_irq_chip(IRQ_WDT, &s3c_irq_level_chip);
	set_irq_handler(IRQ_WDT, handle_level_irq);
	set_irq_chained_handler(IRQ_WDT, s3c_irq_demux_wdtac97);

	for (irqno = IRQ_S3C2440_WDT; irqno <= IRQ_S3C2440_AC97; irqno++) {
		set_irq_chip(irqno, &s3c_irq_wdtac97);
		set_irq_handler(irqno, handle_level_irq);
		set_irq_flags(irqno, IRQF_VALID);
	}

	return 0;
}