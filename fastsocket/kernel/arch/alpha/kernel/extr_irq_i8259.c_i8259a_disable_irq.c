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
 int /*<<< orphan*/  __i8259a_disable_irq (unsigned int) ; 
 int /*<<< orphan*/  i8259_irq_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
i8259a_disable_irq(unsigned int irq)
{
	spin_lock(&i8259_irq_lock);
	__i8259a_disable_irq(irq);
	spin_unlock(&i8259_irq_lock);
}