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
struct mib_mac_mgmt {int /*<<< orphan*/  country_string; int /*<<< orphan*/  multi_domain_capability_enabled; int /*<<< orphan*/  multi_domain_capability_implemented; int /*<<< orphan*/  res; int /*<<< orphan*/  ibss_change; int /*<<< orphan*/  power_mgmt_mode; int /*<<< orphan*/  current_bss_type; int /*<<< orphan*/  current_essid; int /*<<< orphan*/  current_bssid; int /*<<< orphan*/  CFP_period; int /*<<< orphan*/  DTIM_period; int /*<<< orphan*/  privacy_option_implemented; int /*<<< orphan*/  CFP_mode; int /*<<< orphan*/  ATIM_window; int /*<<< orphan*/  station_id; int /*<<< orphan*/  medium_occupancy_limit; int /*<<< orphan*/  CFP_max_duration; int /*<<< orphan*/  beacon_period; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  MIB_MAC_MGMT ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_mac_mgmt*,int) ; 
 int /*<<< orphan*/  hex2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mib_mac_mgmt*) ; 
 struct mib_mac_mgmt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_mac_mgmt(struct at76_priv *priv)
{
	int ret;
	struct mib_mac_mgmt *m = kmalloc(sizeof(struct mib_mac_mgmt),
					 GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MAC_MGMT, m,
			   sizeof(struct mib_mac_mgmt));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_MGMT) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_MGMT: beacon_period %d CFP_max_duration "
		 "%d medium_occupancy_limit %d station_id 0x%x ATIM_window %d "
		 "CFP_mode %d privacy_opt_impl %d DTIM_period %d CFP_period %d "
		 "current_bssid %pM current_essid %s current_bss_type %d "
		 "pm_mode %d ibss_change %d res %d "
		 "multi_domain_capability_implemented %d "
		 "international_roaming %d country_string %.3s",
		 wiphy_name(priv->hw->wiphy), le16_to_cpu(m->beacon_period),
		 le16_to_cpu(m->CFP_max_duration),
		 le16_to_cpu(m->medium_occupancy_limit),
		 le16_to_cpu(m->station_id), le16_to_cpu(m->ATIM_window),
		 m->CFP_mode, m->privacy_option_implemented, m->DTIM_period,
		 m->CFP_period, m->current_bssid,
		 hex2str(m->current_essid, IW_ESSID_MAX_SIZE),
		 m->current_bss_type, m->power_mgmt_mode, m->ibss_change,
		 m->res, m->multi_domain_capability_implemented,
		 m->multi_domain_capability_enabled, m->country_string);
exit:
	kfree(m);
}