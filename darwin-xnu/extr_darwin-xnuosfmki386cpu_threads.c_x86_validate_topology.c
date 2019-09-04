#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lpkg_num; struct TYPE_7__* next; TYPE_2__* lcpus; TYPE_4__* cores; TYPE_3__* dies; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_8__ {int cpu_num; struct TYPE_8__* next_in_pkg; TYPE_1__* package; struct TYPE_8__* next_in_core; TYPE_4__* core; struct TYPE_8__* next_in_die; TYPE_3__* die; } ;
typedef  TYPE_2__ x86_lcpu_t ;
struct TYPE_9__ {int pdie_num; struct TYPE_9__* next_in_pkg; TYPE_2__* lcpus; TYPE_4__* cores; TYPE_1__* package; } ;
typedef  TYPE_3__ x86_die_t ;
struct TYPE_10__ {int pcore_num; struct TYPE_10__* next_in_pkg; TYPE_2__* lcpus; TYPE_1__* package; struct TYPE_10__* next_in_die; TYPE_3__* die; } ;
typedef  TYPE_4__ x86_core_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int nPackages; int nLThreadsPerPackage; int nLCoresPerDie; int nLThreadsPerDie; int nLDiesPerPackage; int nLThreadsPerCore; int nLCoresPerPackage; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOPO_DBG (char*,...) ; 
 int /*<<< orphan*/  debug_topology_print () ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 
 int real_ncpus ; 
 TYPE_6__ topoParms ; 
 scalar_t__ topo_dbg ; 
 TYPE_1__* x86_pkgs ; 

void
x86_validate_topology(void)
{
    x86_pkg_t		*pkg;
    x86_die_t		*die;
    x86_core_t		*core;
    x86_lcpu_t		*lcpu;
    uint32_t		nDies;
    uint32_t		nCores;
    uint32_t		nCPUs;

    if (topo_dbg)
	debug_topology_print();

    /*
     * Called after processors are registered but before non-boot processors
     * are started:
     *  - real_ncpus: number of registered processors driven from MADT
     *  - max_ncpus:  max number of processors that will be started 
     */
    nCPUs = topoParms.nPackages * topoParms.nLThreadsPerPackage;
    if (nCPUs != real_ncpus)
	panic("x86_validate_topology() %d threads but %d registered from MADT",
	      nCPUs, real_ncpus);

    pkg = x86_pkgs;
    while (pkg != NULL) {
	/*
	 * Make sure that the package has the correct number of dies.
	 */
	nDies = 0;
	die = pkg->dies;
	while (die != NULL) {
	    if (die->package == NULL)
		panic("Die(%d)->package is NULL",
		      die->pdie_num);
	    if (die->package != pkg)
		panic("Die %d points to package %d, should be %d",
		      die->pdie_num, die->package->lpkg_num, pkg->lpkg_num);

	    TOPO_DBG("Die(%d)->package %d\n",
		die->pdie_num, pkg->lpkg_num);

	    /*
	     * Make sure that the die has the correct number of cores.
	     */
	    TOPO_DBG("Die(%d)->cores: ", die->pdie_num);
	    nCores = 0;
	    core = die->cores;
	    while (core != NULL) {
		if (core->die == NULL)
		    panic("Core(%d)->die is NULL",
			  core->pcore_num);
		if (core->die != die)
		    panic("Core %d points to die %d, should be %d",
			  core->pcore_num, core->die->pdie_num, die->pdie_num);
		nCores += 1;
		TOPO_DBG("%d ", core->pcore_num);
		core = core->next_in_die;
	    }
	    TOPO_DBG("\n");

	    if (nCores != topoParms.nLCoresPerDie)
		panic("Should have %d Cores, but only found %d for Die %d",
		      topoParms.nLCoresPerDie, nCores, die->pdie_num);

	    /*
	     * Make sure that the die has the correct number of CPUs.
	     */
	    TOPO_DBG("Die(%d)->lcpus: ", die->pdie_num);
	    nCPUs = 0;
	    lcpu = die->lcpus;
	    while (lcpu != NULL) {
		if (lcpu->die == NULL)
		    panic("CPU(%d)->die is NULL",
			  lcpu->cpu_num);
		if (lcpu->die != die)
		    panic("CPU %d points to die %d, should be %d",
			  lcpu->cpu_num, lcpu->die->pdie_num, die->pdie_num);
		nCPUs += 1;
		TOPO_DBG("%d ", lcpu->cpu_num);
		lcpu = lcpu->next_in_die;
	    }
	    TOPO_DBG("\n");

	    if (nCPUs != topoParms.nLThreadsPerDie)
		panic("Should have %d Threads, but only found %d for Die %d",
		      topoParms.nLThreadsPerDie, nCPUs, die->pdie_num);

	    nDies += 1;
	    die = die->next_in_pkg;
	}

	if (nDies != topoParms.nLDiesPerPackage)
	    panic("Should have %d Dies, but only found %d for package %d",
		  topoParms.nLDiesPerPackage, nDies, pkg->lpkg_num);

	/*
	 * Make sure that the package has the correct number of cores.
	 */
	nCores = 0;
	core = pkg->cores;
	while (core != NULL) {
	    if (core->package == NULL)
		panic("Core(%d)->package is NULL",
		      core->pcore_num);
	    if (core->package != pkg)
		panic("Core %d points to package %d, should be %d",
		      core->pcore_num, core->package->lpkg_num, pkg->lpkg_num);
	    TOPO_DBG("Core(%d)->package %d\n",
		core->pcore_num, pkg->lpkg_num);

	    /*
	     * Make sure that the core has the correct number of CPUs.
	     */
	    nCPUs = 0;
	    lcpu = core->lcpus;
	    TOPO_DBG("Core(%d)->lcpus: ", core->pcore_num);
	    while (lcpu != NULL) {
		if (lcpu->core == NULL)
		    panic("CPU(%d)->core is NULL",
			  lcpu->cpu_num);
		if (lcpu->core != core)
		    panic("CPU %d points to core %d, should be %d",
			  lcpu->cpu_num, lcpu->core->pcore_num, core->pcore_num);
		TOPO_DBG("%d ", lcpu->cpu_num);
		nCPUs += 1;
		lcpu = lcpu->next_in_core;
	    }
	    TOPO_DBG("\n");

	    if (nCPUs != topoParms.nLThreadsPerCore)
		panic("Should have %d Threads, but only found %d for Core %d",
		      topoParms.nLThreadsPerCore, nCPUs, core->pcore_num);
	    nCores += 1;
	    core = core->next_in_pkg;
	}

	if (nCores != topoParms.nLCoresPerPackage)
	    panic("Should have %d Cores, but only found %d for package %d",
		  topoParms.nLCoresPerPackage, nCores, pkg->lpkg_num);

	/*
	 * Make sure that the package has the correct number of CPUs.
	 */
	nCPUs = 0;
	lcpu = pkg->lcpus;
	while (lcpu != NULL) {
	    if (lcpu->package == NULL)
		panic("CPU(%d)->package is NULL",
		      lcpu->cpu_num);
	    if (lcpu->package != pkg)
		panic("CPU %d points to package %d, should be %d",
		      lcpu->cpu_num, lcpu->package->lpkg_num, pkg->lpkg_num);
	    TOPO_DBG("CPU(%d)->package %d\n",
		lcpu->cpu_num, pkg->lpkg_num);
	    nCPUs += 1;
	    lcpu = lcpu->next_in_pkg;
	}

	if (nCPUs != topoParms.nLThreadsPerPackage)
	    panic("Should have %d Threads, but only found %d for package %d",
		  topoParms.nLThreadsPerPackage, nCPUs, pkg->lpkg_num);

	pkg = pkg->next;
    }
}