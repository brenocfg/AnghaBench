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
struct ip_vs_sync_mesg {int dummy; } ;
struct ip_vs_sync_buff {TYPE_1__* mesg; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int IP_VS_STATE_MASTER ; 
 struct ip_vs_sync_buff* curr_sb ; 
 int /*<<< orphan*/  curr_sb_lock ; 
 int /*<<< orphan*/  ip_vs_sync_buff_release (struct ip_vs_sync_buff*) ; 
 int ip_vs_sync_state ; 
 int /*<<< orphan*/  sb_queue_tail (struct ip_vs_sync_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int sysctl_ip_vs_sync_ver ; 

void ip_vs_sync_switch_mode(int mode) {
	struct ip_vs_sync_buff *sb;

	spin_lock_bh(&curr_sb_lock);
	if (!(ip_vs_sync_state & IP_VS_STATE_MASTER))
		goto unlock;
	sb = curr_sb;
	if (mode == sysctl_ip_vs_sync_ver || !sb)
		goto unlock;

	/* Buffer empty ? then let buf_create do the job  */
	if (sb->mesg->size <= sizeof(struct ip_vs_sync_mesg)) {
		ip_vs_sync_buff_release(sb);
		curr_sb = NULL;
	} else
		sb_queue_tail(curr_sb);

unlock:
	spin_unlock_bh(&curr_sb_lock);
}