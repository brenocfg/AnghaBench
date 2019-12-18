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
struct wiphy {int flags; int /*<<< orphan*/  regd; } ;
struct regulatory_request {int /*<<< orphan*/  alpha2; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
 int NL80211_REGDOM_SET_BY_CORE ; 
 int NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int /*<<< orphan*/  REG_DBG_PRINT (char*,int /*<<< orphan*/ ) ; 
 int WIPHY_FLAG_CUSTOM_REGULATORY ; 
 int WIPHY_FLAG_STRICT_REGULATORY ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  is_world_regdom (int /*<<< orphan*/ ) ; 
 int reg_dev_ignore_cell_hint (struct wiphy*) ; 
 int /*<<< orphan*/  reg_initiator_name (int) ; 
 scalar_t__ reg_request_cell_base (struct regulatory_request*) ; 

__attribute__((used)) static bool ignore_reg_update(struct wiphy *wiphy,
			      enum nl80211_reg_initiator initiator)
{
	struct regulatory_request *lr = get_last_request();

	if (!lr) {
		REG_DBG_PRINT("Ignoring regulatory request %s since last_request is not set\n",
			      reg_initiator_name(initiator));
		return true;
	}

	if (initiator == NL80211_REGDOM_SET_BY_CORE &&
	    wiphy->flags & WIPHY_FLAG_CUSTOM_REGULATORY) {
		REG_DBG_PRINT("Ignoring regulatory request %s since the driver uses its own custom regulatory domain\n",
			      reg_initiator_name(initiator));
		return true;
	}

	/*
	 * wiphy->regd will be set once the device has its own
	 * desired regulatory domain set
	 */
	if (wiphy->flags & WIPHY_FLAG_STRICT_REGULATORY && !wiphy->regd &&
	    initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    !is_world_regdom(lr->alpha2)) {
		REG_DBG_PRINT("Ignoring regulatory request %s since the driver requires its own regulatory domain to be set first\n",
			      reg_initiator_name(initiator));
		return true;
	}

	if (reg_request_cell_base(lr))
		return reg_dev_ignore_cell_hint(wiphy);

	return false;
}