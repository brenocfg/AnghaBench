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
struct ip_vs_sync_buff {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPVS_SYNC_SEND_DELAY ; 
 scalar_t__ IPVS_SYNC_WAKEUP_RATE ; 
 int IP_VS_STATE_MASTER ; 
 int /*<<< orphan*/  ip_vs_master_wakeup_work ; 
 int /*<<< orphan*/  ip_vs_sync_buff_release (struct ip_vs_sync_buff*) ; 
 int /*<<< orphan*/  ip_vs_sync_lock ; 
 int /*<<< orphan*/  ip_vs_sync_queue ; 
 scalar_t__ ip_vs_sync_queue_delay ; 
 scalar_t__ ip_vs_sync_queue_len ; 
 int ip_vs_sync_state ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_master_thread ; 
 scalar_t__ sysctl_sync_qlen_max () ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sb_queue_tail(struct ip_vs_sync_buff *sb)
{
	spin_lock(&ip_vs_sync_lock);
	if (ip_vs_sync_state & IP_VS_STATE_MASTER &&
	    ip_vs_sync_queue_len < sysctl_sync_qlen_max()) {
		if (!ip_vs_sync_queue_len)
			schedule_delayed_work(&ip_vs_master_wakeup_work,
					      max(IPVS_SYNC_SEND_DELAY, 1));
		ip_vs_sync_queue_len++;
		list_add_tail(&sb->list, &ip_vs_sync_queue);
		if ((++ip_vs_sync_queue_delay) == IPVS_SYNC_WAKEUP_RATE)
			wake_up_process(sync_master_thread);
	} else
		ip_vs_sync_buff_release(sb);
	spin_unlock(&ip_vs_sync_lock);
}