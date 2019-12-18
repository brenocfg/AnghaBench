#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {scalar_t__ cpu_rendezvous_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBOP_STACKSHOT ; 
 int /*<<< orphan*/  DebuggerTrapWithState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  mp_rendezvous_lock () ; 
 int /*<<< orphan*/  mp_rendezvous_unlock () ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static kern_return_t 
stackshot_trap()
{
	kern_return_t	rv;

#if defined(__x86_64__)
	/*
	 * Since mp_rendezvous and stackshot both attempt to capture cpus then perform an
	 * operation, it's essential to apply mutual exclusion to the other when one
	 * mechanism is in operation, lest there be a deadlock as the mechanisms race to
	 * capture CPUs.
	 *
	 * Further, we assert that invoking stackshot from mp_rendezvous*() is not
	 * allowed, so we check to ensure there there is no rendezvous in progress before
	 * trying to grab the lock (if there is, a deadlock will occur when we try to
	 * grab the lock).  This is accomplished by setting cpu_rendezvous_in_progress to
	 * TRUE in the mp rendezvous action function.  If stackshot_trap() is called by
	 * a subordinate of the call chain within the mp rendezvous action, this flag will
	 * be set and can be used to detect the inevitable deadlock that would occur
	 * if this thread tried to grab the rendezvous lock.
	 */

	if (current_cpu_datap()->cpu_rendezvous_in_progress == TRUE) {
		panic("Calling stackshot from a rendezvous is not allowed!");
	}

	mp_rendezvous_lock();
#endif

	rv = DebuggerTrapWithState(DBOP_STACKSHOT, NULL, NULL, NULL, 0, NULL, FALSE, 0);

#if defined(__x86_64__)
	mp_rendezvous_unlock();
#endif
	return (rv);
}