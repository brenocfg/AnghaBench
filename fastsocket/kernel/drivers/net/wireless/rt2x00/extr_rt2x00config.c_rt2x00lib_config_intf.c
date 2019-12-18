#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00intf_conf {int type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac; int /*<<< orphan*/  sync; } ;
struct rt2x00_intf {int dummy; } ;
struct rt2x00_dev {TYPE_2__* ops; int /*<<< orphan*/  intf_sta_count; int /*<<< orphan*/  intf_ap_count; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* config_intf ) (struct rt2x00_dev*,struct rt2x00_intf*,struct rt2x00intf_conf*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int CONFIG_UPDATE_BSSID ; 
 unsigned int CONFIG_UPDATE_MAC ; 
 unsigned int CONFIG_UPDATE_TYPE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  TSF_SYNC_ADHOC ; 
 int /*<<< orphan*/  TSF_SYNC_AP_NONE ; 
 int /*<<< orphan*/  TSF_SYNC_INFRA ; 
 int /*<<< orphan*/  TSF_SYNC_NONE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct rt2x00_intf*,struct rt2x00intf_conf*,unsigned int) ; 

void rt2x00lib_config_intf(struct rt2x00_dev *rt2x00dev,
			   struct rt2x00_intf *intf,
			   enum nl80211_iftype type,
			   const u8 *mac, const u8 *bssid)
{
	struct rt2x00intf_conf conf;
	unsigned int flags = 0;

	conf.type = type;

	switch (type) {
	case NL80211_IFTYPE_ADHOC:
		conf.sync = TSF_SYNC_ADHOC;
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_WDS:
		conf.sync = TSF_SYNC_AP_NONE;
		break;
	case NL80211_IFTYPE_STATION:
		conf.sync = TSF_SYNC_INFRA;
		break;
	default:
		conf.sync = TSF_SYNC_NONE;
		break;
	}

	/*
	 * Note that when NULL is passed as address we will send
	 * 00:00:00:00:00 to the device to clear the address.
	 * This will prevent the device being confused when it wants
	 * to ACK frames or considers itself associated.
	 */
	memset(conf.mac, 0, sizeof(conf.mac));
	if (mac)
		memcpy(conf.mac, mac, ETH_ALEN);

	memset(conf.bssid, 0, sizeof(conf.bssid));
	if (bssid)
		memcpy(conf.bssid, bssid, ETH_ALEN);

	flags |= CONFIG_UPDATE_TYPE;
	if (mac || (!rt2x00dev->intf_ap_count && !rt2x00dev->intf_sta_count))
		flags |= CONFIG_UPDATE_MAC;
	if (bssid || (!rt2x00dev->intf_ap_count && !rt2x00dev->intf_sta_count))
		flags |= CONFIG_UPDATE_BSSID;

	rt2x00dev->ops->lib->config_intf(rt2x00dev, intf, &conf, flags);
}