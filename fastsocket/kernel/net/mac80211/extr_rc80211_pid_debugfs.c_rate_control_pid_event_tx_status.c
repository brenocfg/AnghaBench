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
union rc_pid_event_data {int /*<<< orphan*/  tx_status; int /*<<< orphan*/  flags; } ;
struct rc_pid_event_buffer {int dummy; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PID_EVENT_TYPE_TX_STATUS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_tx_info*,int) ; 
 int /*<<< orphan*/  rate_control_pid_event (struct rc_pid_event_buffer*,int /*<<< orphan*/ ,union rc_pid_event_data*) ; 

void rate_control_pid_event_tx_status(struct rc_pid_event_buffer *buf,
				      struct ieee80211_tx_info *stat)
{
	union rc_pid_event_data evd;

	evd.flags = stat->flags;
	memcpy(&evd.tx_status, stat, sizeof(struct ieee80211_tx_info));
	rate_control_pid_event(buf, RC_PID_EVENT_TYPE_TX_STATUS, &evd);
}