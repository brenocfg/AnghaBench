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
 int /*<<< orphan*/  cpu_possible_bits ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

void init_cpu_possible(const struct cpumask *src)
{
	cpumask_copy(to_cpumask(cpu_possible_bits), src);
}