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
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;

/* Variables and functions */
 scalar_t__ dbg_q_busy ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  dbg_queue ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  queueFreeMsg (int /*<<< orphan*/ ) ; 

void diva_maint_ack_message (int do_release,
                             diva_os_spin_lock_magic_t* old_irql) {
	if (!dbg_q_busy) {
		return;
	}
	if (do_release) {
		queueFreeMsg (dbg_queue);
	}
	dbg_q_busy = 0;
  diva_os_leave_spin_lock (&dbg_q_lock, old_irql, "read_ack");
}