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
struct zd_mac {int /*<<< orphan*/  chip; int /*<<< orphan*/ * vif; int /*<<< orphan*/  type; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_mac_free_cur_beacon (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_set_beacon_interval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_write_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zd_op_remove_interface(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif)
{
	struct zd_mac *mac = zd_hw_mac(hw);
	mac->type = NL80211_IFTYPE_UNSPECIFIED;
	mac->vif = NULL;
	zd_set_beacon_interval(&mac->chip, 0, 0, NL80211_IFTYPE_UNSPECIFIED);
	zd_write_mac_addr(&mac->chip, NULL);

	zd_mac_free_cur_beacon(mac);
}