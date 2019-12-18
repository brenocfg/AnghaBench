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
 int /*<<< orphan*/  cached_irq_mask ; 
 int /*<<< orphan*/  cpu_set_irq_affinity (unsigned int,struct cpumask const) ; 
 int /*<<< orphan*/  dp264_irq_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsunami_update_irq_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dp264_set_affinity(unsigned int irq, const struct cpumask *affinity)
{ 
	spin_lock(&dp264_irq_lock);
	cpu_set_irq_affinity(irq, *affinity);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);

	return 0;
}