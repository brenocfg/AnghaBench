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
union iwreq_data {scalar_t__ mode; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int sync_scan_hurryup; scalar_t__ iw_mode; int /*<<< orphan*/  wx_sem; int /*<<< orphan*/  proto_started; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_protocol (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_protocol (struct ieee80211_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int ieee80211_wx_set_mode(struct ieee80211_device *ieee, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{

	ieee->sync_scan_hurryup = 1;

	down(&ieee->wx_sem);

	if (wrqu->mode == ieee->iw_mode)
		goto out;

	if (wrqu->mode == IW_MODE_MONITOR){

		ieee->dev->type = ARPHRD_IEEE80211;
	}else{
		ieee->dev->type = ARPHRD_ETHER;
	}

	if (!ieee->proto_started){
		ieee->iw_mode = wrqu->mode;
	}else{
		ieee80211_stop_protocol(ieee);
		ieee->iw_mode = wrqu->mode;
		ieee80211_start_protocol(ieee);
	}

out:
	up(&ieee->wx_sem);
	return 0;
}