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
struct station_parameters {int listen_interval; scalar_t__ plink_action; scalar_t__ plink_state; int local_pm; scalar_t__ vlan; int /*<<< orphan*/  sta_modify_mask; void* ext_capab_len; void* ext_capab; int /*<<< orphan*/  capability; void* supported_rates_len; void* supported_rates; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_2__* ieee80211_ptr; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum nl80211_mesh_power_mode { ____Placeholder_nl80211_mesh_power_mode } nl80211_mesh_power_mode ;
struct TYPE_4__ {int iftype; } ;
struct TYPE_3__ {int /*<<< orphan*/  change_station; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 size_t NL80211_ATTR_LOCAL_MESH_POWER_MODE ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_STA_AID ; 
 size_t NL80211_ATTR_STA_CAPABILITY ; 
 size_t NL80211_ATTR_STA_EXT_CAPABILITY ; 
 size_t NL80211_ATTR_STA_LISTEN_INTERVAL ; 
 size_t NL80211_ATTR_STA_PLINK_ACTION ; 
 size_t NL80211_ATTR_STA_PLINK_STATE ; 
 size_t NL80211_ATTR_STA_SUPPORTED_RATES ; 
#define  NL80211_IFTYPE_ADHOC 134 
#define  NL80211_IFTYPE_AP 133 
#define  NL80211_IFTYPE_AP_VLAN 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int NL80211_MESH_POWER_MAX ; 
 int NL80211_MESH_POWER_UNKNOWN ; 
 scalar_t__ NUM_NL80211_PLINK_ACTIONS ; 
 scalar_t__ NUM_NL80211_PLINK_STATES ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  STATION_PARAM_APPLY_CAPABILITY ; 
 int /*<<< orphan*/  STATION_PARAM_APPLY_PLINK_STATE ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 scalar_t__ get_vlan (struct genl_info*,struct net_device*) ; 
 int /*<<< orphan*/  memset (struct station_parameters*,int /*<<< orphan*/ ,int) ; 
 int nl80211_set_station_tdls (struct genl_info*,struct station_parameters*) ; 
 void* nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 
 scalar_t__ parse_station_flags (struct genl_info*,int,struct station_parameters*) ; 
 int rdev_change_station (struct net_device*,struct net_device*,int /*<<< orphan*/ *,struct station_parameters*) ; 

__attribute__((used)) static int nl80211_set_station(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct station_parameters params;
	u8 *mac_addr;
	int err;

	memset(&params, 0, sizeof(params));

	params.listen_interval = -1;

	if (!rdev->ops->change_station)
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_STA_AID])
		return -EINVAL;

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]) {
		params.supported_rates =
			nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
		params.supported_rates_len =
			nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
	}

	if (info->attrs[NL80211_ATTR_STA_CAPABILITY]) {
		params.capability =
			nla_get_u16(info->attrs[NL80211_ATTR_STA_CAPABILITY]);
		params.sta_modify_mask |= STATION_PARAM_APPLY_CAPABILITY;
	}

	if (info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]) {
		params.ext_capab =
			nla_data(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
		params.ext_capab_len =
			nla_len(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
	}

	if (info->attrs[NL80211_ATTR_STA_LISTEN_INTERVAL])
		return -EINVAL;

	if (parse_station_flags(info, dev->ieee80211_ptr->iftype, &params))
		return -EINVAL;

	if (info->attrs[NL80211_ATTR_STA_PLINK_ACTION]) {
		params.plink_action =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_PLINK_ACTION]);
		if (params.plink_action >= NUM_NL80211_PLINK_ACTIONS)
			return -EINVAL;
	}

	if (info->attrs[NL80211_ATTR_STA_PLINK_STATE]) {
		params.plink_state =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_PLINK_STATE]);
		if (params.plink_state >= NUM_NL80211_PLINK_STATES)
			return -EINVAL;
		params.sta_modify_mask |= STATION_PARAM_APPLY_PLINK_STATE;
	}

	if (info->attrs[NL80211_ATTR_LOCAL_MESH_POWER_MODE]) {
		enum nl80211_mesh_power_mode pm = nla_get_u32(
			info->attrs[NL80211_ATTR_LOCAL_MESH_POWER_MODE]);

		if (pm <= NL80211_MESH_POWER_UNKNOWN ||
		    pm > NL80211_MESH_POWER_MAX)
			return -EINVAL;

		params.local_pm = pm;
	}

	/* Include parameters for TDLS peer (will check later) */
	err = nl80211_set_station_tdls(info, &params);
	if (err)
		return err;

	params.vlan = get_vlan(info, rdev);
	if (IS_ERR(params.vlan))
		return PTR_ERR(params.vlan);

	switch (dev->ieee80211_ptr->iftype) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
		break;
	default:
		err = -EOPNOTSUPP;
		goto out_put_vlan;
	}

	/* driver will call cfg80211_check_station_change() */
	err = rdev_change_station(rdev, dev, mac_addr, &params);

 out_put_vlan:
	if (params.vlan)
		dev_put(params.vlan);

	return err;
}