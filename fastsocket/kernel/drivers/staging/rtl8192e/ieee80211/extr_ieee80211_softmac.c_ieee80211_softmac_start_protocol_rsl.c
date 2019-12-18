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
struct ieee80211_device {int /*<<< orphan*/  wx_sem; scalar_t__ sync_scan_hurryup; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_protocol (struct ieee80211_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void ieee80211_softmac_start_protocol(struct ieee80211_device *ieee)
{
	ieee->sync_scan_hurryup = 0;
	down(&ieee->wx_sem);
	ieee80211_start_protocol(ieee);
	up(&ieee->wx_sem);
}