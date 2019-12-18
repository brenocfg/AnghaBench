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
 int /*<<< orphan*/  dynamic_irq_cleanup_x (unsigned int,int) ; 

void dynamic_irq_cleanup(unsigned int irq)
{
	dynamic_irq_cleanup_x(irq, false);
}