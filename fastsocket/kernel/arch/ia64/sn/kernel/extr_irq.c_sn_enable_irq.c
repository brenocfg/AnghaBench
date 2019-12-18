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
 int /*<<< orphan*/  IA64_CPE_VECTOR ; 
 int /*<<< orphan*/  ia64_mca_register_cpev (unsigned int) ; 
 unsigned int local_vector_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sn_enable_irq(unsigned int irq)
{
	if (irq == local_vector_to_irq(IA64_CPE_VECTOR))
		ia64_mca_register_cpev(irq);
}