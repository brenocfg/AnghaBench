#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long icucr; } ;

/* Variables and functions */
 unsigned long PLD_ICUCR_ILEVEL7 ; 
 unsigned int irq2pldirq (unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned long,unsigned long) ; 
 TYPE_1__* pld_icu_data ; 
 unsigned long pldirq2port (unsigned int) ; 

__attribute__((used)) static void disable_opsput_pld_irq(unsigned int irq)
{
	unsigned long port, data;
	unsigned int pldirq;

	pldirq = irq2pldirq(irq);
//	disable_opsput_irq(M32R_IRQ_INT1);
	port = pldirq2port(pldirq);
	data = pld_icu_data[pldirq].icucr|PLD_ICUCR_ILEVEL7;
	outw(data, port);
}