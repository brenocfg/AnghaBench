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
struct TYPE_2__ {int kdebug_slowcheck; int /*<<< orphan*/  kdebug_flags; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KDBG_NOWRAP ; 
 int SLOW_NOLOG ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kds_spin_lock ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ ) ; 
 int ml_set_interrupts_enabled (int) ; 

__attribute__((used)) static void
enable_wrap(uint32_t old_slowcheck)
{
	int s = ml_set_interrupts_enabled(FALSE);
	lck_spin_lock(kds_spin_lock);

	kd_ctrl_page.kdebug_flags &= ~KDBG_NOWRAP;

	if ( !(old_slowcheck & SLOW_NOLOG))
		kd_ctrl_page.kdebug_slowcheck &= ~SLOW_NOLOG;

	lck_spin_unlock(kds_spin_lock);
	ml_set_interrupts_enabled(s);
}