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
struct wiphy {void (* reg_notifier ) (struct wiphy*,struct regulatory_request*) ;int /*<<< orphan*/  flags; } ;
struct ieee80211_regdomain {int dummy; } ;
struct ath_regulatory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  WIPHY_FLAG_CUSTOM_REGULATORY ; 
 int /*<<< orphan*/  WIPHY_FLAG_STRICT_REGULATORY ; 
 struct ieee80211_regdomain* ath_default_world_regdomain () ; 
 scalar_t__ ath_is_world_regd (struct ath_regulatory*) ; 
 int /*<<< orphan*/  ath_reg_apply_radar_flags (struct wiphy*) ; 
 int /*<<< orphan*/  ath_reg_apply_world_flags (struct wiphy*,int /*<<< orphan*/ ,struct ath_regulatory*) ; 
 struct ieee80211_regdomain* ath_world_regdomain (struct ath_regulatory*) ; 
 int /*<<< orphan*/  wiphy_apply_custom_regulatory (struct wiphy*,struct ieee80211_regdomain const*) ; 

__attribute__((used)) static int
ath_regd_init_wiphy(struct ath_regulatory *reg,
		    struct wiphy *wiphy,
		    void (*reg_notifier)(struct wiphy *wiphy,
					 struct regulatory_request *request))
{
	const struct ieee80211_regdomain *regd;

	wiphy->reg_notifier = reg_notifier;
	wiphy->flags |= WIPHY_FLAG_STRICT_REGULATORY;

	if (ath_is_world_regd(reg)) {
		/*
		 * Anything applied here (prior to wiphy registration) gets
		 * saved on the wiphy orig_* parameters
		 */
		regd = ath_world_regdomain(reg);
		wiphy->flags |= WIPHY_FLAG_CUSTOM_REGULATORY;
	} else {
		/*
		 * This gets applied in the case of the absence of CRDA,
		 * it's our own custom world regulatory domain, similar to
		 * cfg80211's but we enable passive scanning.
		 */
		regd = ath_default_world_regdomain();
	}
	wiphy_apply_custom_regulatory(wiphy, regd);
	ath_reg_apply_radar_flags(wiphy);
	ath_reg_apply_world_flags(wiphy, NL80211_REGDOM_SET_BY_DRIVER, reg);
	return 0;
}