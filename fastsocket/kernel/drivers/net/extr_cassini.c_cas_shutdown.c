#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cas {int cas_flags; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  reset_task_pending_all; int /*<<< orphan*/  reset_task_pending_spare; int /*<<< orphan*/  reset_task_pending_mtu; int /*<<< orphan*/  link_timer; scalar_t__ hw_running; } ;

/* Variables and functions */
 int CAS_FLAG_SATURN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_lock_all_save (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  cas_phy_powerdown (struct cas*) ; 
 int /*<<< orphan*/  cas_reset (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_unlock_all_restore (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void cas_shutdown(struct cas *cp)
{
	unsigned long flags;

	/* Make us not-running to avoid timers respawning */
	cp->hw_running = 0;

	del_timer_sync(&cp->link_timer);

	/* Stop the reset task */
#if 0
	while (atomic_read(&cp->reset_task_pending_mtu) ||
	       atomic_read(&cp->reset_task_pending_spare) ||
	       atomic_read(&cp->reset_task_pending_all))
		schedule();

#else
	while (atomic_read(&cp->reset_task_pending))
		schedule();
#endif
	/* Actually stop the chip */
	cas_lock_all_save(cp, flags);
	cas_reset(cp, 0);
	if (cp->cas_flags & CAS_FLAG_SATURN)
		cas_phy_powerdown(cp);
	cas_unlock_all_restore(cp, flags);
}