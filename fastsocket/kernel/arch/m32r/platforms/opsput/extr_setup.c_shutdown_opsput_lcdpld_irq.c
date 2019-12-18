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
 int /*<<< orphan*/  PLD_ICUCR_ILEVEL7 ; 
 unsigned int irq2lcdpldirq (unsigned int) ; 
 unsigned long lcdpldirq2port (unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void shutdown_opsput_lcdpld_irq(unsigned int irq)
{
	unsigned long port;
	unsigned int pldirq;

	pldirq = irq2lcdpldirq(irq);
	port = lcdpldirq2port(pldirq);
	outw(PLD_ICUCR_ILEVEL7, port);
}