#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int dtim_data; int beacon_interval; scalar_t__* last_dtim_sta_time; } ;
struct ieee80211_device {int ps_timeout; int ps; int softmac_features; scalar_t__ mgmt_queue_tail; scalar_t__ mgmt_queue_head; TYPE_2__ current_network; scalar_t__ last_rx_ps_time; TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ trans_start; } ;

/* Variables and functions */
 int IEEE80211_DTIM_INVALID ; 
 int IEEE80211_DTIM_MBCAST ; 
 int IEEE80211_DTIM_UCAST ; 
 int IEEE80211_DTIM_VALID ; 
 int IEEE_SOFTMAC_SINGLE_QUEUE ; 
 scalar_t__ MSECS (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

short ieee80211_sta_ps_sleep(struct ieee80211_device *ieee, u32 *time_h, u32 *time_l)
{
	int timeout = ieee->ps_timeout;
	u8 dtim;
	/*if(ieee->ps == IEEE80211_PS_DISABLED ||
		ieee->iw_mode != IW_MODE_INFRA ||
		ieee->state != IEEE80211_LINKED)

		return 0;
	*/
	dtim = ieee->current_network.dtim_data;
	//printk("DTIM\n");
	if(!(dtim & IEEE80211_DTIM_VALID))
		return 0;
	timeout = ieee->current_network.beacon_interval; //should we use ps_timeout value or beacon_interval
	//printk("VALID\n");
	ieee->current_network.dtim_data = IEEE80211_DTIM_INVALID;

	if(dtim & ((IEEE80211_DTIM_UCAST | IEEE80211_DTIM_MBCAST)& ieee->ps))
		return 2;

	if(!time_after(jiffies, ieee->dev->trans_start + MSECS(timeout)))
		return 0;

	if(!time_after(jiffies, ieee->last_rx_ps_time + MSECS(timeout)))
		return 0;

	if((ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE ) &&
		(ieee->mgmt_queue_tail != ieee->mgmt_queue_head))
		return 0;

	if(time_l){
		*time_l = ieee->current_network.last_dtim_sta_time[0]
			+ (ieee->current_network.beacon_interval);
		//	* ieee->current_network.dtim_period) * 1000;
	}

	if(time_h){
		*time_h = ieee->current_network.last_dtim_sta_time[1];
		if(time_l && *time_l < ieee->current_network.last_dtim_sta_time[0])
			*time_h += 1;
	}

	return 1;


}