#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ lock_data; } ;
struct TYPE_9__ {TYPE_7__ interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_PC (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_SPIN_LOCK_ACQUIRE ; 
 int /*<<< orphan*/  LockTimeOutTSC ; 
 int /*<<< orphan*/  OBTAIN_PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 scalar_t__ hw_lock_to (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ machine_timeout_suspended () ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  pltrace (scalar_t__) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ ) ; 
 TYPE_1__* spinlock_timed_out ; 
 int /*<<< orphan*/  spinlock_timeout_NMI (uintptr_t) ; 
 int /*<<< orphan*/  usld_lock_post (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_lock_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
usimple_lock(
	usimple_lock_t	l)
{
#ifndef	MACHINE_SIMPLE_LOCK
	DECL_PC(pc);

	OBTAIN_PC(pc);
	USLDBG(usld_lock_pre(l, pc));

	if(__improbable(hw_lock_to(&l->interlock, LockTimeOutTSC) == 0))	{
		boolean_t uslock_acquired = FALSE;
		while (machine_timeout_suspended()) {
			enable_preemption();
			if ((uslock_acquired = hw_lock_to(&l->interlock, LockTimeOutTSC)))
				break;
		}

		if (uslock_acquired == FALSE) {
			uint32_t lock_cpu;
			uintptr_t lowner = (uintptr_t)l->interlock.lock_data;
			spinlock_timed_out = l;
			lock_cpu = spinlock_timeout_NMI(lowner);
			panic("Spinlock acquisition timed out: lock=%p, lock owner thread=0x%lx, current_thread: %p, lock owner active on CPU 0x%x, current owner: 0x%lx, time: %llu",
			      l, lowner,  current_thread(), lock_cpu, (uintptr_t)l->interlock.lock_data, mach_absolute_time());
		}
	}
#if DEVELOPMENT || DEBUG
		pltrace(FALSE);
#endif

	USLDBG(usld_lock_post(l, pc));
#else
	simple_lock((simple_lock_t)l);
#endif
#if CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_SPIN_LOCK_ACQUIRE, l, 0);
#endif
}