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
struct TYPE_4__ {int flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct TYPE_6__ {scalar_t__ bBusyTraffic; } ;
struct r8180_priv {int /*<<< orphan*/  wx_sem; struct ieee80211_device* ieee80211; TYPE_3__ link_detect; scalar_t__ bInactivePs; scalar_t__ up; } ;
struct net_device {int dummy; } ;
struct iw_scan_req {scalar_t__ essid_len; int /*<<< orphan*/  essid; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssid; scalar_t__ ssid_len; } ;
struct ieee80211_device {int actscanning; scalar_t__ state; TYPE_2__ current_network; scalar_t__ bHwRadioOff; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  IPSLeave (struct net_device*) ; 
 int IW_SCAN_THIS_ESSID ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_ips_scan_syncro (struct ieee80211_device*) ; 
 int ieee80211_wx_set_scan (struct ieee80211_device*,struct iw_request_info*,union iwreq_data*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8180_wx_set_scan(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	int ret;
	struct ieee80211_device* ieee = priv->ieee80211;


	if(priv->ieee80211->bHwRadioOff)
		return 0;

//YJ,add,080819, for hidden ap
	//printk("==*&*&*&==>%s in\n", __func__);
	//printk("=*&*&*&*===>flag:%x, %x\n", wrqu->data.flags, IW_SCAN_THIS_ESSID);
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
//YJ,add,080819, for hidden ap, end

	down(&priv->wx_sem);
	if(priv->up){
//		printk("set scan ENABLE_IPS\n");
		priv->ieee80211->actscanning = true;
		if(priv->bInactivePs && (priv->ieee80211->state != IEEE80211_LINKED)){
			IPSLeave(dev);
//			down(&priv->ieee80211->wx_sem);

//			if (priv->ieee80211->iw_mode == IW_MODE_MONITOR || !(priv->ieee80211->proto_started)){
//				ret = -1;
//				up(&priv->ieee80211->wx_sem);
//				up(&priv->wx_sem);
//				return ret;
//			}

	//	queue_work(priv->ieee80211->wq, &priv->ieee80211->wx_sync_scan_wq);
		//printk("start scan============================>\n");
		ieee80211_softmac_ips_scan_syncro(priv->ieee80211);
//ieee80211_start_scan(priv->ieee80211);
		/* intentionally forget to up sem */
//			up(&priv->ieee80211->wx_sem);
			ret = 0;
		}
		else
		{
			//YJ,add,080828, prevent scan in BusyTraffic
			//FIXME: Need to consider last scan time
			if ((priv->link_detect.bBusyTraffic) && (true))
			{
				ret = 0;
				printk("Now traffic is busy, please try later!\n");
			}
			else
			//YJ,add,080828, prevent scan in BusyTraffic,end
				ret = ieee80211_wx_set_scan(priv->ieee80211,a,wrqu,b);
		}
	}
	else
		ret = -1;

	up(&priv->wx_sem);

	return ret;
}