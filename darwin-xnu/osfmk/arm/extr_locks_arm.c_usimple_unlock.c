#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
typedef  int /*<<< orphan*/  pc_t ;
struct TYPE_5__ {int /*<<< orphan*/  lck_spin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBTAIN_PC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_lock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  usld_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
usimple_unlock(
	       usimple_lock_t l)
{
#ifndef	MACHINE_SIMPLE_LOCK
	pc_t            pc;

	OBTAIN_PC(pc, l);
	USLDBG(usld_unlock(l, pc));
	sync();
	hw_lock_unlock(&l->lck_spin_data);
#else
	simple_unlock((simple_lock_t) l);
#endif
}