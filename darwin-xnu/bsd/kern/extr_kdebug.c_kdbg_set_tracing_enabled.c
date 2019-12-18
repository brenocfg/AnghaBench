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
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  kdebug_iops; int /*<<< orphan*/  kdebug_slowcheck; int /*<<< orphan*/  oldest_time; } ;

/* Variables and functions */
 int FALSE ; 
 int KDEBUG_ENABLE_PPT ; 
 int KDEBUG_ENABLE_TRACE ; 
 int /*<<< orphan*/  KD_CALLBACK_KDEBUG_DISABLED ; 
 int /*<<< orphan*/  KD_CALLBACK_KDEBUG_ENABLED ; 
 int /*<<< orphan*/  KD_CALLBACK_SYNC_FLUSH ; 
 int /*<<< orphan*/  SLOW_NOLOG ; 
 int /*<<< orphan*/  commpage_update_kdebug_state () ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_iop_list_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdbg_timestamp () ; 
 int kdebug_enable ; 
 int /*<<< orphan*/  kds_spin_lock ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ ) ; 
 int ml_set_interrupts_enabled (int) ; 

__attribute__((used)) static void
kdbg_set_tracing_enabled(boolean_t enabled, uint32_t trace_type)
{
	int s = ml_set_interrupts_enabled(FALSE);
	lck_spin_lock(kds_spin_lock);
	if (enabled) {
		/*
		 * The oldest valid time is now; reject old events from IOPs.
		 */
		kd_ctrl_page.oldest_time = kdbg_timestamp();
		kdebug_enable |= trace_type;
		kd_ctrl_page.kdebug_slowcheck &= ~SLOW_NOLOG;
		kd_ctrl_page.enabled = 1;
		commpage_update_kdebug_state();
	} else {
		kdebug_enable &= ~(KDEBUG_ENABLE_TRACE|KDEBUG_ENABLE_PPT);
		kd_ctrl_page.kdebug_slowcheck |= SLOW_NOLOG;
		kd_ctrl_page.enabled = 0;
		commpage_update_kdebug_state();
	}
	lck_spin_unlock(kds_spin_lock);
	ml_set_interrupts_enabled(s);

	if (enabled) {
		kdbg_iop_list_callback(kd_ctrl_page.kdebug_iops, KD_CALLBACK_KDEBUG_ENABLED, NULL);
	} else {
		/*
		 * If you do not flush the IOP trace buffers, they can linger
		 * for a considerable period; consider code which disables and
		 * deallocates without a final sync flush.
		 */
		kdbg_iop_list_callback(kd_ctrl_page.kdebug_iops, KD_CALLBACK_KDEBUG_DISABLED, NULL);
		kdbg_iop_list_callback(kd_ctrl_page.kdebug_iops, KD_CALLBACK_SYNC_FLUSH, NULL);
	}
}