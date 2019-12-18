#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; scalar_t__ HpetCmp; int /*<<< orphan*/  HpetCfg; TYPE_4__* Hpet; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_10__ {scalar_t__ primary; TYPE_3__* core; } ;
typedef  TYPE_2__ x86_lcpu_t ;
struct TYPE_11__ {scalar_t__ HpetCmp; int /*<<< orphan*/  HpetCfg; TYPE_4__* Hpet; int /*<<< orphan*/  HpetVec; TYPE_1__* package; } ;
typedef  TYPE_3__ x86_core_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  Config; } ;
typedef  TYPE_4__ hpetTimer_t ;
struct TYPE_13__ {int hpetOffset; int /*<<< orphan*/  hpetVector; } ;
typedef  TYPE_5__ hpetRequest_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Tn_INT_ENB_CNF ; 
 int /*<<< orphan*/  X86PKG_FL_HAS_HPET ; 
 TYPE_2__* cpu_to_lcpu (scalar_t__) ; 
 scalar_t__ hpetArea ; 
 int /*<<< orphan*/  hpet_arg ; 
 int hpet_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ml_get_apicid (scalar_t__) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ real_ncpus ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

int
hpet_request(uint32_t cpu)
{
    hpetRequest_t	hpetReq;
    int			rc;
    x86_lcpu_t		*lcpu;
    x86_core_t		*core;
    x86_pkg_t		*pkg;
    boolean_t		enabled;

    if (hpet_req == NULL) {
	return(-1);
    }

    /*
     * Deal with the case where the CPU # passed in is past the
     * value specified in cpus=n in boot-args.
     */
    if (cpu >= real_ncpus) {
	enabled = ml_set_interrupts_enabled(FALSE);
	lcpu = cpu_to_lcpu(cpu);
	if (lcpu != NULL) {
	    core = lcpu->core;
	    pkg  = core->package;

	    if (lcpu->primary) {
		pkg->flags |= X86PKG_FL_HAS_HPET;
	    }
	}

	ml_set_interrupts_enabled(enabled);
	return(0);
    }

    rc = (*hpet_req)(ml_get_apicid(cpu), hpet_arg, &hpetReq);
    if (rc != 0) {
	return(rc);
    }

    enabled = ml_set_interrupts_enabled(FALSE);
    lcpu = cpu_to_lcpu(cpu);
    core = lcpu->core;
    pkg  = core->package;

    /*
     * Compute the address of the HPET.
     */
    core->Hpet = (hpetTimer_t *)((uint8_t *)hpetArea + hpetReq.hpetOffset);
    core->HpetVec = hpetReq.hpetVector;

    /*
     * Enable interrupts
     */
    core->Hpet->Config |= Tn_INT_ENB_CNF;

    /*
     * Save the configuration
     */
    core->HpetCfg = core->Hpet->Config;
    core->HpetCmp = 0;

    /*
     * If the CPU is the "primary" for the package, then
     * add the HPET to the package too.
     */
    if (lcpu->primary) {
	pkg->Hpet = core->Hpet;
	pkg->HpetCfg = core->HpetCfg;
	pkg->HpetCmp = core->HpetCmp;
	pkg->flags |= X86PKG_FL_HAS_HPET;
    }

    ml_set_interrupts_enabled(enabled);

    return(0);
}