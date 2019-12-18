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
 int real_hard_smp_processor_id () ; 

__attribute__((used)) static int irq_choose_cpu(unsigned int virt_irq)
{
	return real_hard_smp_processor_id();
}