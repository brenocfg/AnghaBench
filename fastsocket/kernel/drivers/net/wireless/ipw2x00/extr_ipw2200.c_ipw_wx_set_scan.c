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
struct net_device {int dummy; } ;
struct iw_scan_req {scalar_t__ scan_type; int /*<<< orphan*/  essid; scalar_t__ essid_len; } ;
struct iw_request_info {int dummy; } ;
struct delayed_work {int dummy; } ;
struct ipw_priv {int user_requested_scan; int direct_scan_ssid_len; int /*<<< orphan*/  mutex; struct delayed_work request_scan; struct delayed_work request_passive_scan; struct delayed_work request_direct_scan; int /*<<< orphan*/  direct_scan_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 int IW_SCAN_THIS_ESSID ; 
 scalar_t__ IW_SCAN_TYPE_PASSIVE ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (struct delayed_work*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_wx_set_scan(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct iw_scan_req *req = (struct iw_scan_req *)extra;
	struct delayed_work *work = NULL;

	mutex_lock(&priv->mutex);

	priv->user_requested_scan = 1;

	if (wrqu->data.length == sizeof(struct iw_scan_req)) {
		if (wrqu->data.flags & IW_SCAN_THIS_ESSID) {
			int len = min((int)req->essid_len,
			              (int)sizeof(priv->direct_scan_ssid));
			memcpy(priv->direct_scan_ssid, req->essid, len);
			priv->direct_scan_ssid_len = len;
			work = &priv->request_direct_scan;
		} else if (req->scan_type == IW_SCAN_TYPE_PASSIVE) {
			work = &priv->request_passive_scan;
		}
	} else {
		/* Normal active broadcast scan */
		work = &priv->request_scan;
	}

	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("Start scan\n");

	schedule_delayed_work(work, 0);

	return 0;
}