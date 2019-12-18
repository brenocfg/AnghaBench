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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct iw_scan_req {scalar_t__ essid_len; scalar_t__* essid; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; int flags; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {scalar_t__ iw_mode; scalar_t__ sta_fw_ver; int /*<<< orphan*/  scan_timestamp; int /*<<< orphan*/  dev_enabled; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int ENETDOWN ; 
 int EOPNOTSUPP ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int IW_SCAN_THIS_ESSID ; 
 scalar_t__ PRISM2_FW_VER (int,int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int prism2_request_hostscan (struct net_device*,scalar_t__*,scalar_t__) ; 
 int prism2_request_scan (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_siwscan(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_point *data, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int ret;
	u8 *ssid = NULL, ssid_len = 0;
	struct iw_scan_req *req = (struct iw_scan_req *) extra;

	iface = netdev_priv(dev);
	local = iface->local;

	if (data->length < sizeof(struct iw_scan_req))
		req = NULL;

	if (local->iw_mode == IW_MODE_MASTER) {
		/* In master mode, we just return the results of our local
		 * tables, so we don't need to start anything...
		 * Jean II */
		data->length = 0;
		return 0;
	}

	if (!local->dev_enabled)
		return -ENETDOWN;

	if (req && data->flags & IW_SCAN_THIS_ESSID) {
		ssid = req->essid;
		ssid_len = req->essid_len;

		if (ssid_len &&
		    ((local->iw_mode != IW_MODE_INFRA &&
		      local->iw_mode != IW_MODE_ADHOC) ||
		     (local->sta_fw_ver < PRISM2_FW_VER(1,3,1))))
			return -EOPNOTSUPP;
	}

	if (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1))
		ret = prism2_request_hostscan(dev, ssid, ssid_len);
	else
		ret = prism2_request_scan(dev);

	if (ret == 0)
		local->scan_timestamp = jiffies;

	/* Could inquire F101, F103 or wait for SIOCGIWSCAN and read RID */

	return ret;
}