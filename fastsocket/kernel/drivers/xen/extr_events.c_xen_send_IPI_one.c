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
typedef  enum ipi_vector { ____Placeholder_ipi_vector } ipi_vector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 int /*<<< orphan*/  notify_remote_via_irq (int) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

void xen_send_IPI_one(unsigned int cpu, enum ipi_vector vector)
{
	int irq = per_cpu(ipi_to_irq, cpu)[vector];
	BUG_ON(irq < 0);
	notify_remote_via_irq(irq);
}