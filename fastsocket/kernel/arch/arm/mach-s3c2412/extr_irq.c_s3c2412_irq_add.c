#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sys_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_wake; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_VALID ; 
 unsigned int IRQ_EINT0 ; 
 unsigned int IRQ_EINT3 ; 
 unsigned int IRQ_RTC ; 
 unsigned int IRQ_S3C2412_CF ; 
 int /*<<< orphan*/  IRQ_S3C2412_CFSDI ; 
 unsigned int IRQ_S3C2412_SDI ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 TYPE_1__ s3c2412_irq_cfsdi ; 
 int /*<<< orphan*/  s3c2412_irq_demux_cfsdi ; 
 TYPE_1__ s3c2412_irq_eint0t4 ; 
 TYPE_1__ s3c2412_irq_rtc_chip ; 
 int /*<<< orphan*/  s3c2412_irq_rtc_wake ; 
 TYPE_1__ s3c_irq_chip ; 
 int /*<<< orphan*/  set_irq_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  set_irq_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2412_irq_add(struct sys_device *sysdev)
{
	unsigned int irqno;

	for (irqno = IRQ_EINT0; irqno <= IRQ_EINT3; irqno++) {
		set_irq_chip(irqno, &s3c2412_irq_eint0t4);
		set_irq_handler(irqno, handle_edge_irq);
		set_irq_flags(irqno, IRQF_VALID);
	}

	/* add demux support for CF/SDI */

	set_irq_chained_handler(IRQ_S3C2412_CFSDI, s3c2412_irq_demux_cfsdi);

	for (irqno = IRQ_S3C2412_SDI; irqno <= IRQ_S3C2412_CF; irqno++) {
		set_irq_chip(irqno, &s3c2412_irq_cfsdi);
		set_irq_handler(irqno, handle_level_irq);
		set_irq_flags(irqno, IRQF_VALID);
	}

	/* change RTC IRQ's set wake method */

	s3c2412_irq_rtc_chip = s3c_irq_chip;
	s3c2412_irq_rtc_chip.set_wake = s3c2412_irq_rtc_wake;

	set_irq_chip(IRQ_RTC, &s3c2412_irq_rtc_chip);

	return 0;
}