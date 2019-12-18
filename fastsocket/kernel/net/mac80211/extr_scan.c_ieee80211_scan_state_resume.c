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
struct ieee80211_local {int /*<<< orphan*/  next_scan_state; int /*<<< orphan*/  leave_oper_channel_time; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ flush; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SCAN_SET_CHANNEL ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_offchannel_stop_vifs (struct ieee80211_local*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void ieee80211_scan_state_resume(struct ieee80211_local *local,
					unsigned long *next_delay)
{
	ieee80211_offchannel_stop_vifs(local);

	if (local->ops->flush) {
		ieee80211_flush_queues(local, NULL);
		*next_delay = 0;
	} else
		*next_delay = HZ / 10;

	/* remember when we left the operating channel */
	local->leave_oper_channel_time = jiffies;

	/* advance to the next channel to be scanned */
	local->next_scan_state = SCAN_SET_CHANNEL;
}