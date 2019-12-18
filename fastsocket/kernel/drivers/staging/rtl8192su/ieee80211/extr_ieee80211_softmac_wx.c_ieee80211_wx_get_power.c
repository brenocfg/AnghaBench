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
struct TYPE_2__ {int disabled; int flags; int value; } ;
union iwreq_data {TYPE_1__ power; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int ps; int ps_timeout; int ps_period; int /*<<< orphan*/  wx_sem; } ;

/* Variables and functions */
 int IEEE80211_PS_DISABLED ; 
 int IEEE80211_PS_MBCAST ; 
 int IEEE80211_PS_UNICAST ; 
 int IW_POWER_ALL_R ; 
 int IW_POWER_MULTICAST_R ; 
 int IW_POWER_PERIOD ; 
 int IW_POWER_TIMEOUT ; 
 int IW_POWER_TYPE ; 
 int IW_POWER_UNICAST_R ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int ieee80211_wx_get_power(struct ieee80211_device *ieee,
				 struct iw_request_info *info,
				 union iwreq_data *wrqu, char *extra)
{
	int ret =0;

	down(&ieee->wx_sem);

	if(ieee->ps == IEEE80211_PS_DISABLED){
		wrqu->power.disabled = 1;
		goto exit;
	}

	wrqu->power.disabled = 0;

	if ((wrqu->power.flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) {
		wrqu->power.flags = IW_POWER_TIMEOUT;
		wrqu->power.value = ieee->ps_timeout * 1000;
	} else {
//		ret = -EOPNOTSUPP;
//		goto exit;
		wrqu->power.flags = IW_POWER_PERIOD;
		wrqu->power.value = ieee->ps_period * 1000;
//ieee->current_network.dtim_period * ieee->current_network.beacon_interval * 1024;
	}

       if ((ieee->ps & (IEEE80211_PS_MBCAST | IEEE80211_PS_UNICAST)) == (IEEE80211_PS_MBCAST | IEEE80211_PS_UNICAST))
	   	wrqu->power.flags |= IW_POWER_ALL_R;
	else if (ieee->ps & IEEE80211_PS_MBCAST)
		wrqu->power.flags |= IW_POWER_MULTICAST_R;
	else
		wrqu->power.flags |= IW_POWER_UNICAST_R;

exit:
	up(&ieee->wx_sem);
	return ret;

}