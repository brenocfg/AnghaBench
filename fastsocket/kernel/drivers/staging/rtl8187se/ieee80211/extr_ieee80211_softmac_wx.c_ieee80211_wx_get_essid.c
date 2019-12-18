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
struct TYPE_4__ {int length; int flags; } ;
union iwreq_data {TYPE_2__ essid; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {char* ssid; int ssid_len; } ;
struct ieee80211_device {scalar_t__ iw_mode; scalar_t__ state; scalar_t__ ssid_set; int /*<<< orphan*/  lock; TYPE_1__ current_network; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IEEE80211_LINKED_SCANNING ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int ieee80211_wx_get_essid(struct ieee80211_device *ieee, struct iw_request_info *a,union iwreq_data *wrqu,char *b)
{
	int len,ret = 0;
	unsigned long flags;

	if (ieee->iw_mode == IW_MODE_MONITOR)
		return -1;

	/* We want avoid to give to the user inconsistent infos*/
	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->current_network.ssid[0] == '\0' ||
		ieee->current_network.ssid_len == 0){
		ret = -1;
		goto out;
	}

	if (ieee->state != IEEE80211_LINKED &&
		ieee->state != IEEE80211_LINKED_SCANNING &&
		ieee->ssid_set == 0){
		ret = -1;
		goto out;
	}
	len = ieee->current_network.ssid_len;
	wrqu->essid.length = len;
	strncpy(b,ieee->current_network.ssid,len);
	wrqu->essid.flags = 1;

out:
	spin_unlock_irqrestore(&ieee->lock, flags);

	return ret;

}