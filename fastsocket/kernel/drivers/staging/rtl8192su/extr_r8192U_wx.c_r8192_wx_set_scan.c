#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
union iwreq_data {TYPE_2__ data; } ;
struct r8192_priv {int /*<<< orphan*/  wx_sem; struct ieee80211_device* ieee80211; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct iw_scan_req {scalar_t__ essid_len; int /*<<< orphan*/  essid; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ssid; scalar_t__ ssid_len; } ;
struct TYPE_4__ {int bBusyTraffic; } ;
struct ieee80211_device {scalar_t__ state; scalar_t__ scanning; TYPE_3__ current_network; TYPE_1__ LinkDetectInfo; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENETDOWN ; 
 scalar_t__ IEEE80211_LINKED ; 
 int IW_SCAN_THIS_ESSID ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_scan_syncro (struct ieee80211_device*) ; 
 int ieee80211_wx_set_scan (struct ieee80211_device*,struct iw_request_info*,union iwreq_data*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8192_wx_set_scan(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device* ieee = priv->ieee80211;
	int ret = 0;

	if(!priv->up) return -ENETDOWN;

	if (priv->ieee80211->LinkDetectInfo.bBusyTraffic == true)
		return -EAGAIN;

	if (wrqu->data.flags & IW_SCAN_THIS_ESSID)
	{
		struct iw_scan_req* req = (struct iw_scan_req*)b;
		if (req->essid_len)
		{
			//printk("==**&*&*&**===>scan set ssid:%s\n", req->essid);
			ieee->current_network.ssid_len = req->essid_len;
			memcpy(ieee->current_network.ssid, req->essid, req->essid_len);
			//printk("=====>network ssid:%s\n", ieee->current_network.ssid);
		}
	}

	down(&priv->wx_sem);
	if(priv->ieee80211->state != IEEE80211_LINKED){
                priv->ieee80211->scanning = 0;
                ieee80211_softmac_scan_syncro(priv->ieee80211);
                ret = 0;
        }
	else
	ret = ieee80211_wx_set_scan(priv->ieee80211,a,wrqu,b);
	up(&priv->wx_sem);
	return ret;
}