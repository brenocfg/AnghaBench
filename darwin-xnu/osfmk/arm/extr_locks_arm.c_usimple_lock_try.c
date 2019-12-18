#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
typedef  int /*<<< orphan*/  pc_t ;
struct TYPE_6__ {int /*<<< orphan*/  lck_spin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBTAIN_PC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 unsigned int hw_lock_try (int /*<<< orphan*/ *) ; 
 unsigned int simple_lock_try (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_lock_try_post (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usld_lock_try_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 

unsigned int
usimple_lock_try(
		 usimple_lock_t l)
{
#ifndef	MACHINE_SIMPLE_LOCK
	pc_t            pc;
	unsigned int    success;

	OBTAIN_PC(pc, l);
	USLDBG(usld_lock_try_pre(l, pc));
	if ((success = hw_lock_try(&l->lck_spin_data))) {
		USLDBG(usld_lock_try_post(l, pc));
	}
	return success;
#else
	return (simple_lock_try((simple_lock_t) l));
#endif
}