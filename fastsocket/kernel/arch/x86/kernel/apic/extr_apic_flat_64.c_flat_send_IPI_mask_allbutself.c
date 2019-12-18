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
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  _flat_send_IPI_mask (unsigned long,int) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 unsigned long* cpumask_bits (struct cpumask const*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void
 flat_send_IPI_mask_allbutself(const struct cpumask *cpumask, int vector)
{
	unsigned long mask = cpumask_bits(cpumask)[0];
	int cpu = smp_processor_id();

	if (cpu < BITS_PER_LONG)
		clear_bit(cpu, &mask);

	_flat_send_IPI_mask(mask, vector);
}