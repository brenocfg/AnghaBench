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
 int /*<<< orphan*/  clear_irq_vector (unsigned int) ; 
 int /*<<< orphan*/  dynamic_irq_cleanup (unsigned int) ; 

void destroy_irq(unsigned int irq)
{
	dynamic_irq_cleanup(irq);
	clear_irq_vector(irq);
}