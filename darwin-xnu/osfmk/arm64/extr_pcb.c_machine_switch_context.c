#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  cpu_data_t ;
struct TYPE_14__ {int /*<<< orphan*/ * CpuDatap; } ;
struct TYPE_15__ {TYPE_2__ machine; TYPE_1__* map; } ;
struct TYPE_13__ {scalar_t__ pmap; } ;

/* Variables and functions */
 TYPE_3__* Switch_context (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getCpuDatap () ; 
 int /*<<< orphan*/  kpc_off_cpu (TYPE_3__*) ; 
 int /*<<< orphan*/  machine_switch_context_kprintf (char*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_switch (scalar_t__) ; 

thread_t
machine_switch_context(
		       thread_t old,
		       thread_continue_t continuation,
		       thread_t new)
{
	thread_t retval;
	pmap_t          new_pmap;
	cpu_data_t	*cpu_data_ptr;

#define machine_switch_context_kprintf(x...)	/* kprintf("machine_switch_con
						 * text: " x) */

	cpu_data_ptr = getCpuDatap();
	if (old == new)
		panic("machine_switch_context");

	kpc_off_cpu(old);


	new_pmap = new->map->pmap;
	if (old->map->pmap != new_pmap)
		pmap_switch(new_pmap);

	new->machine.CpuDatap = cpu_data_ptr;

	machine_switch_context_kprintf("old= %x contination = %x new = %x\n", old, continuation, new);

	retval = Switch_context(old, continuation, new);
	assert(retval != NULL);

	return retval;
}