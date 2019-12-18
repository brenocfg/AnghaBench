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
struct ieee80211_device {int /*<<< orphan*/  beacon_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_send_beacon (struct ieee80211_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_send_beacon_cb(unsigned long _ieee)
{
	struct ieee80211_device *ieee =
		(struct ieee80211_device *) _ieee;
	unsigned long flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);
	ieee80211_send_beacon(ieee);
	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
}