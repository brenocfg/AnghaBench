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
struct wireless_dev {int iftype; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; scalar_t__ flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_STATION 128 
 int cfg80211_ibss_wext_giwessid (struct net_device*,struct iw_request_info*,struct iw_point*,char*) ; 
 int cfg80211_mgd_wext_giwessid (struct net_device*,struct iw_request_info*,struct iw_point*,char*) ; 

__attribute__((used)) static int cfg80211_wext_giwessid(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_point *data, char *ssid)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	data->flags = 0;
	data->length = 0;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_ADHOC:
		return cfg80211_ibss_wext_giwessid(dev, info, data, ssid);
	case NL80211_IFTYPE_STATION:
		return cfg80211_mgd_wext_giwessid(dev, info, data, ssid);
	default:
		return -EOPNOTSUPP;
	}
}