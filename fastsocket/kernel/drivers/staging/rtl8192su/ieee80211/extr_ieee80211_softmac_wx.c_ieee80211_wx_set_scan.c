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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {scalar_t__ iw_mode; scalar_t__ state; int /*<<< orphan*/  wx_sem; int /*<<< orphan*/  wx_sync_scan_wq; int /*<<< orphan*/  wq; int /*<<< orphan*/  proto_started; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int ieee80211_wx_set_scan(struct ieee80211_device *ieee, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	int ret = 0;

	down(&ieee->wx_sem);

	if (ieee->iw_mode == IW_MODE_MONITOR || !(ieee->proto_started)){
		ret = -1;
		goto out;
	}

	if ( ieee->state == IEEE80211_LINKED){
		queue_work(ieee->wq, &ieee->wx_sync_scan_wq);
		/* intentionally forget to up sem */
		return 0;
	}

out:
	up(&ieee->wx_sem);
	return ret;
}