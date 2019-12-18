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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sun4u_irq_enable (unsigned int) ; 

__attribute__((used)) static int sun4u_set_affinity(unsigned int virt_irq,
			       const struct cpumask *mask)
{
	sun4u_irq_enable(virt_irq);

	return 0;
}