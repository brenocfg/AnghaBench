#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  scalar_t__ thread_t ;
struct real_descriptor {int dummy; } ;
struct cpu_desc_table {int dummy; } ;
struct TYPE_10__ {int cpu_number; int cpu_int_stack_top; int /*<<< orphan*/ * cpu_ldtp; struct cpu_desc_table* cpu_desc_tablep; int /*<<< orphan*/ * cpu_nanotime; void* cpu_NMI_acknowledged; scalar_t__ cpu_active_thread; int /*<<< orphan*/ * cd_shadow; struct TYPE_10__* cpu_this; int /*<<< orphan*/  cpu_pmap; int /*<<< orphan*/ * cpu_processor; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pcldts; } ;
typedef  TYPE_2__ cldt_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* FALSE ; 
 int INTSTACK_SIZE ; 
 int KERN_SUCCESS ; 
 int LDTSZ ; 
 int MAX_CPUS ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_CPU ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/ * cpshadows ; 
 TYPE_1__** cpu_data_ptr ; 
 TYPE_1__* cpu_datap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_processor_alloc (void*) ; 
 int dyn_dblmap (int,int) ; 
 TYPE_2__* dyn_ldts ; 
 int /*<<< orphan*/  kernel_map ; 
 int kmem_alloc (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kprintf (char*,int,TYPE_1__*,struct cpu_desc_table*,int /*<<< orphan*/ *,long,long) ; 
 int ldt_alias_offset ; 
 int /*<<< orphan*/  mca_cpu_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  ncpus_lock ; 
 int /*<<< orphan*/  pal_rtc_nanotime_info ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pmap_cpu_alloc (void*) ; 
 int real_ncpus ; 
 int round_page_64 (int) ; 
 TYPE_1__* scdatas ; 
 int /*<<< orphan*/ * scdtables ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

cpu_data_t *
cpu_data_alloc(boolean_t is_boot_cpu)
{
	int		ret;
	cpu_data_t	*cdp;

	if (is_boot_cpu) {
		assert(real_ncpus == 1);
		cdp = cpu_datap(0);
		if (cdp->cpu_processor == NULL) {
			simple_lock_init(&ncpus_lock, 0);
			cdp->cpu_processor = cpu_processor_alloc(TRUE);
#if NCOPY_WINDOWS > 0
			cdp->cpu_pmap = pmap_cpu_alloc(TRUE);
#endif
		}
		return cdp;
	}

	boolean_t do_ldt_alloc = FALSE;
	simple_lock(&ncpus_lock);
	int cnum = real_ncpus;
	real_ncpus++;
	if (dyn_ldts == NULL) {
		do_ldt_alloc = TRUE;
	}
	simple_unlock(&ncpus_lock);

	/*
	 * Allocate per-cpu data:
	 */

	cdp = &scdatas[cnum];
	bzero((void*) cdp, sizeof(cpu_data_t));
	cdp->cpu_this = cdp;
	cdp->cpu_number = cnum;
	cdp->cd_shadow = &cpshadows[cnum];
	/*
	 * Allocate interrupt stack:
	 */
	ret = kmem_alloc(kernel_map, 
			 (vm_offset_t *) &cdp->cpu_int_stack_top,
			 INTSTACK_SIZE, VM_KERN_MEMORY_CPU);
	if (ret != KERN_SUCCESS) {
		panic("cpu_data_alloc() int stack failed, ret=%d\n", ret);
	}
	bzero((void*) cdp->cpu_int_stack_top, INTSTACK_SIZE);
	cdp->cpu_int_stack_top += INTSTACK_SIZE;

	/*
	 * Allocate descriptor table:
	 */

	cdp->cpu_desc_tablep = (struct cpu_desc_table *) &scdtables[cnum];
	/*
	 * Allocate LDT
	 */
	if (do_ldt_alloc) {
		boolean_t do_ldt_free = FALSE;
		vm_offset_t sldtoffset = 0;
		/*
		 * Allocate LDT
		 */
		vm_offset_t ldtalloc = 0, ldtallocsz = round_page_64(MAX_CPUS * sizeof(struct real_descriptor) * LDTSZ);
		ret = kmem_alloc(kernel_map, (vm_offset_t *) &ldtalloc, ldtallocsz, VM_KERN_MEMORY_CPU);
		if (ret != KERN_SUCCESS) {
			panic("cpu_data_alloc() ldt failed, kmem_alloc=%d\n", ret);
		}

		simple_lock(&ncpus_lock);
		if (dyn_ldts == NULL) {
			dyn_ldts = (cldt_t *)ldtalloc;
		} else {
			do_ldt_free = TRUE;
		}
		simple_unlock(&ncpus_lock);

		if (do_ldt_free) {
			kmem_free(kernel_map, ldtalloc, ldtallocsz);
		} else {
			/* CPU registration and startup are expected to execute
			 * serially, as invoked by the platform driver.
			 * Create trampoline alias of LDT region.
			 */
			sldtoffset = dyn_dblmap(ldtalloc, ldtallocsz);
			ldt_alias_offset = sldtoffset;
		}
	}
	cdp->cpu_ldtp = &dyn_ldts[cnum].pcldts[0];

#if CONFIG_MCA
	/* Machine-check shadow register allocation. */
	mca_cpu_alloc(cdp);
#endif

	/*
	 * Before this cpu has been assigned a real thread context,
	 * we give it a fake, unique, non-zero thread id which the locking
	 * primitives use as their lock value.
	 * Note that this does not apply to the boot processor, cpu 0, which
	 * transitions to a thread context well before other processors are
	 * started.
	 */
	cdp->cpu_active_thread = (thread_t) (uintptr_t) cdp->cpu_number;
	cdp->cpu_NMI_acknowledged = TRUE;
	cdp->cpu_nanotime = &pal_rtc_nanotime_info;

	kprintf("cpu_data_alloc(%d) %p desc_table: %p "
		"ldt: %p "
		"int_stack: 0x%lx-0x%lx\n",
		cdp->cpu_number, cdp, cdp->cpu_desc_tablep, cdp->cpu_ldtp,
		(long)(cdp->cpu_int_stack_top - INTSTACK_SIZE), (long)(cdp->cpu_int_stack_top));
	cpu_data_ptr[cnum] = cdp;

	return cdp;

}