#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
struct TYPE_4__ {int /*<<< orphan*/  interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBTAIN_PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_lock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  pltrace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock_rwmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
usimple_unlock(
	usimple_lock_t	l)
{
#ifndef	MACHINE_SIMPLE_LOCK
	DECL_PC(pc);

	OBTAIN_PC(pc);
	USLDBG(usld_unlock(l, pc));
#if DEVELOPMENT || DEBUG
		pltrace(TRUE);
#endif
	hw_lock_unlock(&l->interlock);
#else
	simple_unlock_rwmb((simple_lock_t)l);
#endif
}