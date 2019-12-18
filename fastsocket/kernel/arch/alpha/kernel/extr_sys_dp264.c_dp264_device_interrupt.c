#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long csr; } ;
struct TYPE_4__ {TYPE_1__ dir0; } ;

/* Variables and functions */
 TYPE_2__* TSUNAMI_cchip ; 
 unsigned int ffz (unsigned long) ; 
 int /*<<< orphan*/  handle_irq (int) ; 
 int /*<<< orphan*/  isa_device_interrupt (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printk (char*) ; 
 unsigned long tmp ; 

__attribute__((used)) static void
dp264_device_interrupt(unsigned long vector)
{
#if 1
	printk("dp264_device_interrupt: NOT IMPLEMENTED YET!! \n");
#else
	unsigned long pld;
	unsigned int i;

	/* Read the interrupt summary register of TSUNAMI */
	pld = TSUNAMI_cchip->dir0.csr;

	/*
	 * Now for every possible bit set, work through them and call
	 * the appropriate interrupt handler.
	 */
	while (pld) {
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		if (i == 55)
			isa_device_interrupt(vector);
		else
			handle_irq(16 + i);
#if 0
		TSUNAMI_cchip->dir0.csr = 1UL << i; mb();
		tmp = TSUNAMI_cchip->dir0.csr;
#endif
	}
#endif
}