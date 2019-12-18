#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_8__ {int dtms_access; TYPE_1__* dtms_difo; } ;
typedef  TYPE_2__ dtrace_mstate_t ;
struct TYPE_10__ {size_t cpu_id; } ;
struct TYPE_9__ {scalar_t__ cpuc_dtrace_illval; } ;
struct TYPE_7__ {size_t dtdo_strlen; scalar_t__ dtdo_strtab; } ;

/* Variables and functions */
 TYPE_6__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_KPRIV ; 
 int DTRACE_ACCESS_KERNEL ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ DTRACE_INRANGE (scalar_t__,size_t,uintptr_t,size_t) ; 
 int /*<<< orphan*/  DTRACE_RANGE_REMAIN (size_t*,scalar_t__,scalar_t__,size_t) ; 
 TYPE_5__* cpu_core ; 
 scalar_t__ dtrace_canstore_remains (scalar_t__,size_t,size_t*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_canload_remains(uint64_t addr, size_t sz, size_t *remain,
	dtrace_mstate_t *mstate, dtrace_vstate_t *vstate)
{
	volatile uint64_t *illval = &cpu_core[CPU->cpu_id].cpuc_dtrace_illval;

	/*
	 * If we hold the privilege to read from kernel memory, then
	 * everything is readable.
	 */
	if ((mstate->dtms_access & DTRACE_ACCESS_KERNEL) != 0) {
		DTRACE_RANGE_REMAIN(remain, addr, addr, sz);
		return (1);
	}

	/*
	 * You can obviously read that which you can store.
	 */
	if (dtrace_canstore_remains(addr, sz, remain, mstate, vstate))
		return (1);

	/*
	 * We're allowed to read from our own string table.
	 */
	if (DTRACE_INRANGE(addr, sz, (uintptr_t)mstate->dtms_difo->dtdo_strtab,
	    mstate->dtms_difo->dtdo_strlen)) {
		DTRACE_RANGE_REMAIN(remain, addr,
			mstate->dtms_difo->dtdo_strtab,
			mstate->dtms_difo->dtdo_strlen);
		return (1);
	}

	DTRACE_CPUFLAG_SET(CPU_DTRACE_KPRIV);
	*illval = addr;
	return (0);
}