#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_6__ {int /*<<< orphan*/  primary_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_id; TYPE_2__* processor_set; void* is_SMT; struct TYPE_5__* processor_secondary; struct TYPE_5__* processor_primary; } ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_bit_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

void
processor_set_primary(
	processor_t		processor,
	processor_t		primary)
{
	assert(processor->processor_primary == primary || processor->processor_primary == processor);
	/* Re-adjust primary point for this (possibly) secondary processor */
	processor->processor_primary = primary;

	assert(primary->processor_secondary == NULL || primary->processor_secondary == processor);
	if (primary != processor) {
		/* Link primary to secondary, assumes a 2-way SMT model
		 * We'll need to move to a queue if any future architecture
		 * requires otherwise.
		 */
		assert(processor->processor_secondary == NULL);
		primary->processor_secondary = processor;
		/* Mark both processors as SMT siblings */
		primary->is_SMT = TRUE;
		processor->is_SMT = TRUE;

		processor_set_t pset = processor->processor_set;
		atomic_bit_clear(&pset->primary_map, processor->cpu_id, memory_order_relaxed);
	}
}