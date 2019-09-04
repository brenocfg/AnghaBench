#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ppkg_num; int flags; int /*<<< orphan*/  lpkg_num; struct TYPE_8__* next; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_9__ {int cpu_phys_number; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_10__ {int nPThreadsPerPackage; int /*<<< orphan*/  nPackages; } ;

/* Variables and functions */
 int X86PKG_FL_PRESENT ; 
 int X86PKG_FL_READY ; 
 int /*<<< orphan*/  atomic_incl (long*,int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 TYPE_2__* cpu_datap (int) ; 
 TYPE_1__* free_pkgs ; 
 TYPE_1__* kalloc (int) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__ topoParms ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((used)) static x86_pkg_t *
x86_package_alloc(int cpu)
{
    x86_pkg_t	*pkg;
    cpu_data_t	*cpup;

    cpup = cpu_datap(cpu);

    mp_safe_spin_lock(&x86_topo_lock);
    if (free_pkgs != NULL) {
	pkg = free_pkgs;
	free_pkgs = pkg->next;
	pkg->next = NULL;
	simple_unlock(&x86_topo_lock);
    } else {
	simple_unlock(&x86_topo_lock);
	pkg = kalloc(sizeof(x86_pkg_t));
	if (pkg == NULL)
	    panic("x86_package_alloc() kalloc of x86_pkg_t failed!\n");
    }

    bzero((void *) pkg, sizeof(x86_pkg_t));

    pkg->ppkg_num = cpup->cpu_phys_number / topoParms.nPThreadsPerPackage;

    pkg->lpkg_num = topoParms.nPackages;
    atomic_incl((long *) &topoParms.nPackages, 1);

    pkg->flags = X86PKG_FL_PRESENT | X86PKG_FL_READY;
    return(pkg);
}