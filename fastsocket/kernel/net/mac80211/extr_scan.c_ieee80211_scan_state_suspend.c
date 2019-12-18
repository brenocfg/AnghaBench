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
struct ieee80211_local {int /*<<< orphan*/  next_scan_state; int /*<<< orphan*/ * scan_channel; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_CHANNEL ; 
 int /*<<< orphan*/  SCAN_RESUME ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_offchannel_return (struct ieee80211_local*) ; 

__attribute__((used)) static void ieee80211_scan_state_suspend(struct ieee80211_local *local,
					 unsigned long *next_delay)
{
	/* switch back to the operating channel */
	local->scan_channel = NULL;
	ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);

	/* disable PS */
	ieee80211_offchannel_return(local);

	*next_delay = HZ / 5;
	/* afterwards, resume scan & go to next channel */
	local->next_scan_state = SCAN_RESUME;
}