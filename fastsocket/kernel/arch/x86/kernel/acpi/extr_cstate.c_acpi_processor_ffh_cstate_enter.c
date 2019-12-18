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
struct cstate_entry {TYPE_1__* states; } ;
struct acpi_processor_cx {size_t index; } ;
struct TYPE_2__ {int /*<<< orphan*/  ecx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_cstate_entry ; 
 int /*<<< orphan*/  mwait_idle_with_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cstate_entry* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int smp_processor_id () ; 

void acpi_processor_ffh_cstate_enter(struct acpi_processor_cx *cx)
{
	unsigned int cpu = smp_processor_id();
	struct cstate_entry *percpu_entry;

	percpu_entry = per_cpu_ptr(cpu_cstate_entry, cpu);
	mwait_idle_with_hints(percpu_entry->states[cx->index].eax,
	                      percpu_entry->states[cx->index].ecx);
}