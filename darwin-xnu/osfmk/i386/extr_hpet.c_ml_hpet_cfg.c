#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int HpetVec; int /*<<< orphan*/  flags; scalar_t__ HpetCmp; int /*<<< orphan*/  HpetCfg; TYPE_4__* Hpet; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_8__ {int /*<<< orphan*/  primary; TYPE_3__* core; } ;
typedef  TYPE_2__ x86_lcpu_t ;
struct TYPE_9__ {int HpetVec; scalar_t__ HpetCmp; int /*<<< orphan*/  HpetCfg; TYPE_4__* Hpet; TYPE_1__* package; } ;
typedef  TYPE_3__ x86_core_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  Config; } ;
typedef  TYPE_4__ hpetTimer_t ;
struct TYPE_11__ {int /*<<< orphan*/  TIM1_CONF; } ;
typedef  TYPE_5__ hpetReg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Tn_INT_ENB_CNF ; 
 int /*<<< orphan*/  X86PKG_FL_HAS_HPET ; 
 TYPE_2__* cpu_to_lcpu (int) ; 
 scalar_t__ hpetArea ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
ml_hpet_cfg(uint32_t cpu, uint32_t hpetVect)
{
	uint64_t	*hpetVaddr;
	hpetTimer_t	*hpet;
	x86_lcpu_t	*lcpu;
	x86_core_t	*core;
	x86_pkg_t	*pkg;
	boolean_t	enabled;
	
	if(cpu > 1) {
		panic("ml_hpet_cfg: invalid cpu = %d\n", cpu);
	}

	lcpu = cpu_to_lcpu(cpu);
	core = lcpu->core;
	pkg  = core->package;

	/*
	 * Only deal with the primary CPU for the package.
	 */
	if (!lcpu->primary)
	    return;

	enabled = ml_set_interrupts_enabled(FALSE);

	/* Calculate address of the HPET for this processor */
	hpetVaddr = (uint64_t *)(((uintptr_t)&(((hpetReg_t *)hpetArea)->TIM1_CONF)) + (cpu << 5));
	hpet = (hpetTimer_t *)hpetVaddr;

	DBG("ml_hpet_cfg: HPET for cpu %d at %p, vector = %d\n",
	     cpu, hpetVaddr, hpetVect);

	/* Save the address and vector of the HPET for this processor */
	core->Hpet = hpet;
	core->HpetVec = hpetVect;

	/*
	 * Enable interrupts
	 */
	core->Hpet->Config |= Tn_INT_ENB_CNF;

	/* Save the configuration */
	core->HpetCfg = core->Hpet->Config;
	core->HpetCmp = 0;

	/*
	 * We're only doing this for the primary CPU, so go
	 * ahead and add the HPET to the package too.
	 */
	pkg->Hpet = core->Hpet;
	pkg->HpetVec = core->HpetVec;
	pkg->HpetCfg = core->HpetCfg;
	pkg->HpetCmp = core->HpetCmp;
	pkg->flags |= X86PKG_FL_HAS_HPET;

	ml_set_interrupts_enabled(enabled);
}