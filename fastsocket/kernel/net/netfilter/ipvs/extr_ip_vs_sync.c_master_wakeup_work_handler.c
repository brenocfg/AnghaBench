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
struct work_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPVS_SYNC_WAKEUP_RATE ; 
 int /*<<< orphan*/  ip_vs_sync_lock ; 
 scalar_t__ ip_vs_sync_queue_delay ; 
 scalar_t__ ip_vs_sync_queue_len ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_master_thread ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void master_wakeup_work_handler(struct work_struct *work)
{
	spin_lock_bh(&ip_vs_sync_lock);
	if (ip_vs_sync_queue_len &&
	    ip_vs_sync_queue_delay < IPVS_SYNC_WAKEUP_RATE) {
		ip_vs_sync_queue_delay = IPVS_SYNC_WAKEUP_RATE;
		wake_up_process(sync_master_thread);
	}
	spin_unlock_bh(&ip_vs_sync_lock);
}