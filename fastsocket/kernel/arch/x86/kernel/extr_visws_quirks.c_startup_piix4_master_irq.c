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
 int /*<<< orphan*/  init_8259A (int /*<<< orphan*/ ) ; 
 unsigned int startup_cobalt_irq (unsigned int) ; 

__attribute__((used)) static unsigned int startup_piix4_master_irq(unsigned int irq)
{
	init_8259A(0);

	return startup_cobalt_irq(irq);
}