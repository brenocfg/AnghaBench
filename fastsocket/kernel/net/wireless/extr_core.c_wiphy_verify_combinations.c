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
typedef  int u32 ;
typedef  int u16 ;
struct wiphy {int n_iface_combinations; int software_iftypes; int interface_modes; struct ieee80211_iface_combination* iface_combinations; } ;
struct ieee80211_iface_combination {int max_interfaces; int num_different_channels; int n_limits; TYPE_1__* limits; scalar_t__ radar_detect_widths; } ;
struct TYPE_2__ {int types; int max; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CFG80211_MAX_NUM_DIFFERENT_CHANNELS ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int wiphy_verify_combinations(struct wiphy *wiphy)
{
	const struct ieee80211_iface_combination *c;
	int i, j;

	for (i = 0; i < wiphy->n_iface_combinations; i++) {
		u32 cnt = 0;
		u16 all_iftypes = 0;

		c = &wiphy->iface_combinations[i];

		/*
		 * Combinations with just one interface aren't real,
		 * however we make an exception for DFS.
		 */
		if (WARN_ON((c->max_interfaces < 2) && !c->radar_detect_widths))
			return -EINVAL;

		/* Need at least one channel */
		if (WARN_ON(!c->num_different_channels))
			return -EINVAL;

		/*
		 * Put a sane limit on maximum number of different
		 * channels to simplify channel accounting code.
		 */
		if (WARN_ON(c->num_different_channels >
				CFG80211_MAX_NUM_DIFFERENT_CHANNELS))
			return -EINVAL;

		/* DFS only works on one channel. */
		if (WARN_ON(c->radar_detect_widths &&
			    (c->num_different_channels > 1)))
			return -EINVAL;

		if (WARN_ON(!c->n_limits))
			return -EINVAL;

		for (j = 0; j < c->n_limits; j++) {
			u16 types = c->limits[j].types;

			/*
			 * interface types shouldn't overlap, this is
			 * used in cfg80211_can_change_interface()
			 */
			if (WARN_ON(types & all_iftypes))
				return -EINVAL;
			all_iftypes |= types;

			if (WARN_ON(!c->limits[j].max))
				return -EINVAL;

			/* Shouldn't list software iftypes in combinations! */
			if (WARN_ON(wiphy->software_iftypes & types))
				return -EINVAL;

			/* Only a single P2P_DEVICE can be allowed */
			if (WARN_ON(types & BIT(NL80211_IFTYPE_P2P_DEVICE) &&
				    c->limits[j].max > 1))
				return -EINVAL;

			cnt += c->limits[j].max;
			/*
			 * Don't advertise an unsupported type
			 * in a combination.
			 */
			if (WARN_ON((wiphy->interface_modes & types) != types))
				return -EINVAL;
		}

		/* You can't even choose that many! */
		if (WARN_ON(cnt < c->max_interfaces))
			return -EINVAL;
	}

	return 0;
}