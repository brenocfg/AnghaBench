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
typedef  int uint32_t ;
typedef  int boolean_t ;
struct TYPE_2__ {int kdebug_slowcheck; int kdebug_flags; } ;

/* Variables and functions */
 int FALSE ; 
 int KDBG_NOWRAP ; 
 int KDBG_WRAPPED ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kds_spin_lock ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ ) ; 
 int ml_set_interrupts_enabled (int) ; 

__attribute__((used)) static boolean_t
disable_wrap(uint32_t *old_slowcheck, uint32_t *old_flags)
{
	boolean_t wrapped;
	int s = ml_set_interrupts_enabled(FALSE);
	lck_spin_lock(kds_spin_lock);

	*old_slowcheck = kd_ctrl_page.kdebug_slowcheck;
	*old_flags = kd_ctrl_page.kdebug_flags;

	wrapped = kd_ctrl_page.kdebug_flags & KDBG_WRAPPED;
	kd_ctrl_page.kdebug_flags &= ~KDBG_WRAPPED;
	kd_ctrl_page.kdebug_flags |= KDBG_NOWRAP;

	lck_spin_unlock(kds_spin_lock);
	ml_set_interrupts_enabled(s);

	return wrapped;
}