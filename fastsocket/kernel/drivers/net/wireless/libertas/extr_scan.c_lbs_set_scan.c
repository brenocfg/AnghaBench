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
struct TYPE_2__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int scan_channel; scalar_t__ surpriseremoved; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_thread; scalar_t__ scan_ssid_len; int /*<<< orphan*/  scan_ssid; int /*<<< orphan*/  radio_on; } ;
struct iw_scan_req {int /*<<< orphan*/  essid; scalar_t__ essid_len; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_SSID_BUF (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENETDOWN ; 
 int IW_SCAN_THIS_ESSID ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  print_ssid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssid ; 

int lbs_set_scan(struct net_device *dev, struct iw_request_info *info,
		 union iwreq_data *wrqu, char *extra)
{
	DECLARE_SSID_BUF(ssid);
	struct lbs_private *priv = dev->ml_priv;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (!priv->radio_on) {
		ret = -EINVAL;
		goto out;
	}

	if (!netif_running(dev)) {
		ret = -ENETDOWN;
		goto out;
	}

	/* mac80211 does this:
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	if (sdata->type != IEEE80211_IF_TYPE_xxx) {
		ret = -EOPNOTSUPP;
		goto out;
	}
	*/

	if (wrqu->data.length == sizeof(struct iw_scan_req) &&
	    wrqu->data.flags & IW_SCAN_THIS_ESSID) {
		struct iw_scan_req *req = (struct iw_scan_req *)extra;
		priv->scan_ssid_len = req->essid_len;
		memcpy(priv->scan_ssid, req->essid, priv->scan_ssid_len);
		lbs_deb_wext("set_scan, essid '%s'\n",
			print_ssid(ssid, priv->scan_ssid, priv->scan_ssid_len));
	} else {
		priv->scan_ssid_len = 0;
	}

	if (!delayed_work_pending(&priv->scan_work))
		queue_delayed_work(priv->work_thread, &priv->scan_work,
				   msecs_to_jiffies(50));
	/* set marker that currently a scan is taking place */
	priv->scan_channel = -1;

	if (priv->surpriseremoved)
		ret = -EIO;

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}