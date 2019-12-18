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
struct ieee80211_iface_limit {int max; int /*<<< orphan*/  types; } ;
struct rt2x00_dev {TYPE_3__* hw; struct ieee80211_iface_combination* if_combinations; TYPE_1__* ops; struct ieee80211_iface_limit if_limits_ap; } ;
struct ieee80211_iface_combination {int n_limits; int max_interfaces; int num_different_channels; struct ieee80211_iface_limit* limits; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {int n_iface_combinations; struct ieee80211_iface_combination* iface_combinations; } ;
struct TYPE_4__ {int max_ap_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 size_t IF_COMB_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 

__attribute__((used)) static inline void rt2x00lib_set_if_combinations(struct rt2x00_dev *rt2x00dev)
{
	struct ieee80211_iface_limit *if_limit;
	struct ieee80211_iface_combination *if_combination;

	if (rt2x00dev->ops->max_ap_intf < 2)
		return;

	/*
	 * Build up AP interface limits structure.
	 */
	if_limit = &rt2x00dev->if_limits_ap;
	if_limit->max = rt2x00dev->ops->max_ap_intf;
	if_limit->types = BIT(NL80211_IFTYPE_AP);
#ifdef CONFIG_MAC80211_MESH
	if_limit->types |= BIT(NL80211_IFTYPE_MESH_POINT);
#endif

	/*
	 * Build up AP interface combinations structure.
	 */
	if_combination = &rt2x00dev->if_combinations[IF_COMB_AP];
	if_combination->limits = if_limit;
	if_combination->n_limits = 1;
	if_combination->max_interfaces = if_limit->max;
	if_combination->num_different_channels = 1;

	/*
	 * Finally, specify the possible combinations to mac80211.
	 */
	rt2x00dev->hw->wiphy->iface_combinations = rt2x00dev->if_combinations;
	rt2x00dev->hw->wiphy->n_iface_combinations = 1;
}