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
struct TYPE_7__ {int ppkg_num; int lpkg_num; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_8__ {int cpu_num; int pnum; int master; int primary; int lnum; TYPE_1__* package; TYPE_3__* die; TYPE_4__* core; } ;
typedef  TYPE_2__ x86_lcpu_t ;
struct TYPE_9__ {int pdie_num; int ldie_num; } ;
typedef  TYPE_3__ x86_die_t ;
struct TYPE_10__ {int pcore_num; int lcore_num; } ;
typedef  TYPE_4__ x86_core_t ;
struct TYPE_11__ {int nLThreadsPerPackage; int nLThreadsPerCore; int nLCoresPerDie; int nLDiesPerPackage; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int master_cpu ; 
 TYPE_6__ topoParms ; 

void
x86_set_logical_topology(x86_lcpu_t *lcpu, int pnum, int lnum)
{
    x86_core_t	*core = lcpu->core;
    x86_die_t	*die  = lcpu->die;
    x86_pkg_t	*pkg  = lcpu->package;
    
    assert(core != NULL);
    assert(die != NULL);
    assert(pkg != NULL);

    lcpu->cpu_num = lnum;
    lcpu->pnum = pnum;
    lcpu->master = (lnum == master_cpu);
    lcpu->primary = (lnum % topoParms.nLThreadsPerPackage) == 0;

    lcpu->lnum = lnum % topoParms.nLThreadsPerCore;

    core->pcore_num = lnum / topoParms.nLThreadsPerCore;
    core->lcore_num = core->pcore_num % topoParms.nLCoresPerDie;

    die->pdie_num = lnum / (topoParms.nLThreadsPerCore*topoParms.nLCoresPerDie);
    die->ldie_num = die->pdie_num % topoParms.nLDiesPerPackage;

    pkg->ppkg_num = lnum / topoParms.nLThreadsPerPackage;
    pkg->lpkg_num = pkg->ppkg_num;

}