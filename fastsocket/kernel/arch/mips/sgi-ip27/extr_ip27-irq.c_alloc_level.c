#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct slice_data {int* level_to_irq; } ;
struct hub_data {int /*<<< orphan*/  irq_alloc_mask; } ;
struct TYPE_2__ {struct slice_data* data; } ;

/* Variables and functions */
 int LEVELS_PER_SLICE ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cpu_data ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 struct hub_data* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static inline int alloc_level(int cpu, int irq)
{
	struct hub_data *hub = hub_data(cpu_to_node(cpu));
	struct slice_data *si = cpu_data[cpu].data;
	int level;

	level = find_first_zero_bit(hub->irq_alloc_mask, LEVELS_PER_SLICE);
	if (level >= LEVELS_PER_SLICE)
		panic("Cpu %d flooded with devices\n", cpu);

	__set_bit(level, hub->irq_alloc_mask);
	si->level_to_irq[level] = irq;

	return level;
}