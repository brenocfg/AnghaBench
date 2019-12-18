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
 unsigned long M32R_ICUCR_IEN ; 
 unsigned long M32R_ICUCR_ILEVEL6 ; 
 unsigned int NR_IRQS ; 
 TYPE_1__* icu_data ; 
 unsigned long irq2port (unsigned int) ; 
 int /*<<< orphan*/  outl (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static void enable_mappi3_irq(unsigned int irq)
{
	unsigned long port, data;

	if ((irq == 0) ||(irq >= NR_IRQS))  {
		printk("bad irq 0x%08x\n", irq);
		return;
	}
	port = irq2port(irq);
	data = icu_data[irq].icucr|M32R_ICUCR_IEN|M32R_ICUCR_ILEVEL6;
	outl(data, port);
}