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
typedef  int /*<<< orphan*/  cpuid_t ;

/* Variables and functions */
 int find_level (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  intr_connect_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void enable_bridge_irq(unsigned int irq)
{
	cpuid_t cpu;
	int swlevel;

	swlevel = find_level(&cpu, irq);	/* Criminal offence */
	intr_connect_level(cpu, swlevel);
}