#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct TYPE_19__ {struct TYPE_19__* next; } ;
typedef  TYPE_1__ x86_pkg_t ;
typedef  int /*<<< orphan*/  x86_die_t ;
struct TYPE_20__ {int /*<<< orphan*/  package; int /*<<< orphan*/  die; } ;
typedef  TYPE_2__ x86_core_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/  lcpu; int /*<<< orphan*/  cpu_threadtype; int /*<<< orphan*/  cpu_phys_number; } ;
typedef  TYPE_3__ cpu_data_t ;
struct TYPE_18__ {int physical_cpu_max; int logical_cpu_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_THREADTYPE_INTEL_HTT ; 
 int /*<<< orphan*/  CPU_THREADTYPE_NONE ; 
 TYPE_3__* cpu_datap (int) ; 
 scalar_t__ cpu_is_hyperthreaded () ; 
 int /*<<< orphan*/  initTopoParms () ; 
 TYPE_16__ machine_info ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  topoParmsInited ; 
 int /*<<< orphan*/  x86_core_add_lcpu (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* x86_core_alloc (int) ; 
 TYPE_2__* x86_core_find (int) ; 
 int /*<<< orphan*/  x86_core_free (TYPE_2__*) ; 
 int /*<<< orphan*/  x86_die_add_core (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  x86_die_add_lcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * x86_die_alloc (int) ; 
 int /*<<< orphan*/ * x86_die_find (int) ; 
 int /*<<< orphan*/  x86_die_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_lcpu_add_caches (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_lcpu_init (int) ; 
 int /*<<< orphan*/  x86_package_add_core (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  x86_package_add_die (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_package_add_lcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* x86_package_alloc (int) ; 
 TYPE_1__* x86_package_find (int) ; 
 int /*<<< orphan*/  x86_package_free (TYPE_1__*) ; 
 TYPE_1__* x86_pkgs ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void *
cpu_thread_alloc(int cpu)
{
    x86_core_t	*core		= NULL;
    x86_die_t	*die		= NULL;
    x86_pkg_t	*pkg		= NULL;
    cpu_data_t	*cpup;
    uint32_t	phys_cpu;

    /*
     * Only allow one to manipulate the topology at a time.
     */
    mp_safe_spin_lock(&x86_topo_lock);

    /*
     * Make sure all of the topology parameters have been initialized.
     */
    if (!topoParmsInited)
	initTopoParms();

    cpup = cpu_datap(cpu);

    phys_cpu = cpup->cpu_phys_number;

    x86_lcpu_init(cpu);

    /*
     * Assume that all cpus have the same features.
     */
    if (cpu_is_hyperthreaded()) {
	cpup->cpu_threadtype = CPU_THREADTYPE_INTEL_HTT;
    } else {
	cpup->cpu_threadtype = CPU_THREADTYPE_NONE;
    }

    /*
     * Get the package that the logical CPU is in.
     */
    do {
	pkg = x86_package_find(cpu);
	if (pkg == NULL) {
	    /*
	     * Package structure hasn't been created yet, do it now.
	     */
	    simple_unlock(&x86_topo_lock);
	    pkg = x86_package_alloc(cpu);
	    mp_safe_spin_lock(&x86_topo_lock);
	    if (x86_package_find(cpu) != NULL) {
		x86_package_free(pkg);
		continue;
	    }
	    
	    /*
	     * Add the new package to the global list of packages.
	     */
	    pkg->next = x86_pkgs;
	    x86_pkgs = pkg;
	}
    } while (pkg == NULL);

    /*
     * Get the die that the logical CPU is in.
     */
    do {
	die = x86_die_find(cpu);
	if (die == NULL) {
	    /*
	     * Die structure hasn't been created yet, do it now.
	     */
	    simple_unlock(&x86_topo_lock);
	    die = x86_die_alloc(cpu);
	    mp_safe_spin_lock(&x86_topo_lock);
	    if (x86_die_find(cpu) != NULL) {
		x86_die_free(die);
		continue;
	    }

	    /*
	     * Add the die to the package.
	     */
	    x86_package_add_die(pkg, die);
	}
    } while (die == NULL);

    /*
     * Get the core for this logical CPU.
     */
    do {
	core = x86_core_find(cpu);
	if (core == NULL) {
	    /*
	     * Allocate the core structure now.
	     */
	    simple_unlock(&x86_topo_lock);
	    core = x86_core_alloc(cpu);
	    mp_safe_spin_lock(&x86_topo_lock);
	    if (x86_core_find(cpu) != NULL) {
		x86_core_free(core);
		continue;
	    }

	    /*
	     * Add the core to the die & package.
	     */
	    x86_die_add_core(die, core);
	    x86_package_add_core(pkg, core);
	    machine_info.physical_cpu_max += 1;
	}
    } while (core == NULL);

    
    /*
     * Done manipulating the topology, so others can get in.
     */
    machine_info.logical_cpu_max += 1;
    simple_unlock(&x86_topo_lock);

    /*
     * Add the logical CPU to the other topology structures.
     */
    x86_core_add_lcpu(core, &cpup->lcpu);
    x86_die_add_lcpu(core->die, &cpup->lcpu);
    x86_package_add_lcpu(core->package, &cpup->lcpu);
    x86_lcpu_add_caches(&cpup->lcpu);

    return (void *) core;
}