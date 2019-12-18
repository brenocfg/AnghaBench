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
 int /*<<< orphan*/  local_rm9k_perfcounter_irq_shutdown ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void rm9k_perfcounter_irq_shutdown(unsigned int irq)
{
	on_each_cpu(local_rm9k_perfcounter_irq_shutdown, (void *) irq, 1);
}