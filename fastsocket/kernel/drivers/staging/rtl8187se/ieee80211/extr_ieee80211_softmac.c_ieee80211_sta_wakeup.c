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
struct ieee80211_device {int sta_sleep; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* ps_request_tx_ack ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sta_wake_up ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_sta_ps_send_null_frame (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

void ieee80211_sta_wakeup(struct ieee80211_device *ieee, short nl)
{
	if(ieee->sta_sleep == 0){
		if(nl){
		//	printk("Warning: driver is probably failing to report TX ps error\n");
			ieee->ps_request_tx_ack(ieee->dev);
			ieee80211_sta_ps_send_null_frame(ieee, 0);
		}
		return;

	}

	if(ieee->sta_sleep == 1)
		ieee->sta_wake_up(ieee->dev);

	ieee->sta_sleep = 0;

	if(nl){
		ieee->ps_request_tx_ack(ieee->dev);
		ieee80211_sta_ps_send_null_frame(ieee, 0);
	}
}