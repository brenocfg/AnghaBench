#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ppkg_num; struct TYPE_7__* next; } ;
typedef  TYPE_1__ x86_pkg_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int cpu_phys_number; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_9__ {int nPThreadsPerPackage; } ;

/* Variables and functions */
 TYPE_2__* cpu_datap (int) ; 
 TYPE_5__ topoParms ; 
 TYPE_1__* x86_pkgs ; 

__attribute__((used)) static x86_pkg_t *
x86_package_find(int cpu)
{
    x86_pkg_t	*pkg;
    cpu_data_t	*cpup;
    uint32_t	pkg_num;

    cpup = cpu_datap(cpu);

    pkg_num = cpup->cpu_phys_number / topoParms.nPThreadsPerPackage;

    pkg = x86_pkgs;
    while (pkg != NULL) {
	if (pkg->ppkg_num == pkg_num)
	    break;
	pkg = pkg->next;
    }

    return(pkg);
}