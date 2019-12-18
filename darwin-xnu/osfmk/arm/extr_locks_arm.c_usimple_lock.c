#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
typedef  int /*<<< orphan*/  pc_t ;
struct TYPE_7__ {int /*<<< orphan*/  lck_spin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LockTimeOut ; 
 int /*<<< orphan*/  OBTAIN_PC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  hw_lock_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_lock_post (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_lock_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
usimple_lock(
	     usimple_lock_t l)
{
#ifndef	MACHINE_SIMPLE_LOCK
	pc_t            pc;

	OBTAIN_PC(pc, l);
	USLDBG(usld_lock_pre(l, pc));

	if (!hw_lock_to(&l->lck_spin_data, LockTimeOut))	/* Try to get the lock
							 * with a timeout */
		panic("simple lock deadlock detection - l=%p, cpu=%d, ret=%p", &l, cpu_number(), pc);

	USLDBG(usld_lock_post(l, pc));
#else
	simple_lock((simple_lock_t) l);
#endif
}