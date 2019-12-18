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
struct iw_freq {int e; int m; } ;
union iwreq_data {struct iw_freq freq; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_2__ {int channel; } ;
struct ieee80211_device {scalar_t__ iw_mode; scalar_t__ state; int /*<<< orphan*/  wx_sem; TYPE_1__ current_network; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_chan ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_send_beacons (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_send_beacons (struct ieee80211_device*) ; 
 int* ieee80211_wlan_frequencies ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int ieee80211_wx_set_freq(struct ieee80211_device *ieee, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	int ret;
	struct iw_freq *fwrq = & wrqu->freq;
//	printk("in %s\n",__func__);
	down(&ieee->wx_sem);

	if(ieee->iw_mode == IW_MODE_INFRA){
		ret = -EOPNOTSUPP;
		goto out;
	}

	/* if setting by freq convert to channel */
	if (fwrq->e == 1) {
		if ((fwrq->m >= (int) 2.412e8 &&
		     fwrq->m <= (int) 2.487e8)) {
			int f = fwrq->m / 100000;
			int c = 0;

			while ((c < 14) && (f != ieee80211_wlan_frequencies[c]))
				c++;

			/* hack to fall through */
			fwrq->e = 0;
			fwrq->m = c + 1;
		}
	}

	if (fwrq->e > 0 || fwrq->m > 14 || fwrq->m < 1 ){
		ret = -EOPNOTSUPP;
		goto out;

	}else { /* Set the channel */


		ieee->current_network.channel = fwrq->m;
		ieee->set_chan(ieee->dev, ieee->current_network.channel);

		if(ieee->iw_mode == IW_MODE_ADHOC || ieee->iw_mode == IW_MODE_MASTER)
			if(ieee->state == IEEE80211_LINKED){

			ieee80211_stop_send_beacons(ieee);
			ieee80211_start_send_beacons(ieee);
			}
	}

	ret = 0;
out:
	up(&ieee->wx_sem);
	return ret;
}