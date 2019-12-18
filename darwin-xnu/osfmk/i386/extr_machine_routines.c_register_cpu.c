#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * processor_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/ * core; } ;
struct TYPE_7__ {int cpu_number; int /*<<< orphan*/ * cpu_console_buf; int /*<<< orphan*/ * cpu_pmap; int /*<<< orphan*/ * cpu_processor; TYPE_1__ lcpu; int /*<<< orphan*/  cpu_phys_number; } ;
typedef  TYPE_2__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * console_cpu_alloc (scalar_t__) ; 
 int /*<<< orphan*/  console_cpu_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* cpu_data_alloc (scalar_t__) ; 
 int /*<<< orphan*/ * cpu_processor_alloc (scalar_t__) ; 
 int /*<<< orphan*/  cpu_processor_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_thread_alloc (int) ; 
 scalar_t__ kpc_register_cpu (TYPE_2__*) ; 
 int /*<<< orphan*/  kpc_unregister_cpu (TYPE_2__*) ; 
 int /*<<< orphan*/  lapic_cpu_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmap_cpu_alloc (scalar_t__) ; 
 int /*<<< orphan*/  pmap_cpu_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static kern_return_t
register_cpu(
        uint32_t        lapic_id,
	processor_t     *processor_out,
	boolean_t       boot_cpu )
{
	int		target_cpu;
	cpu_data_t	*this_cpu_datap;

	this_cpu_datap = cpu_data_alloc(boot_cpu);
	if (this_cpu_datap == NULL) {
		return KERN_FAILURE;
	}
	target_cpu = this_cpu_datap->cpu_number;
	assert((boot_cpu && (target_cpu == 0)) ||
	      (!boot_cpu && (target_cpu != 0)));

	lapic_cpu_map(lapic_id, target_cpu);

	/* The cpu_id is not known at registration phase. Just do
	 * lapic_id for now 
	 */
	this_cpu_datap->cpu_phys_number = lapic_id;

	this_cpu_datap->cpu_console_buf = console_cpu_alloc(boot_cpu);
	if (this_cpu_datap->cpu_console_buf == NULL)
		goto failed;

#if KPC
	if (kpc_register_cpu(this_cpu_datap) != TRUE)
		goto failed;
#endif

	if (!boot_cpu) {
		cpu_thread_alloc(this_cpu_datap->cpu_number);
		if (this_cpu_datap->lcpu.core == NULL)
			goto failed;

#if NCOPY_WINDOWS > 0
		this_cpu_datap->cpu_pmap = pmap_cpu_alloc(boot_cpu);
		if (this_cpu_datap->cpu_pmap == NULL)
			goto failed;
#endif

		this_cpu_datap->cpu_processor = cpu_processor_alloc(boot_cpu);
		if (this_cpu_datap->cpu_processor == NULL)
			goto failed;
		/*
		 * processor_init() deferred to topology start
		 * because "slot numbers" a.k.a. logical processor numbers
	 	 * are not yet finalized.
		 */
	}

	*processor_out = this_cpu_datap->cpu_processor;

	return KERN_SUCCESS;

failed:
	cpu_processor_free(this_cpu_datap->cpu_processor);
#if NCOPY_WINDOWS > 0
	pmap_cpu_free(this_cpu_datap->cpu_pmap);
#endif
	console_cpu_free(this_cpu_datap->cpu_console_buf);
#if KPC
	kpc_unregister_cpu(this_cpu_datap);
#endif /* KPC */

	return KERN_FAILURE;
}