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
struct irq_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_irq_chip_data (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ps3_host_unmap(struct irq_host *h, unsigned int virq)
{
	set_irq_chip_data(virq, NULL);
}