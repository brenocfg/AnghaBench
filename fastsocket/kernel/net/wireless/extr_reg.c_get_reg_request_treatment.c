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
struct wiphy {int dummy; } ;
struct regulatory_request {int initiator; int /*<<< orphan*/  alpha2; int /*<<< orphan*/  intersect; int /*<<< orphan*/  wiphy_idx; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
 int EINVAL ; 
#define  NL80211_REGDOM_SET_BY_CORE 131 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 130 
#define  NL80211_REGDOM_SET_BY_DRIVER 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int REG_REQ_ALREADY_SET ; 
 int REG_REQ_IGNORE ; 
 int REG_REQ_INTERSECT ; 
 int REG_REQ_OK ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  is_an_alpha2 (int /*<<< orphan*/ ) ; 
 int reg_ignore_cell_hint (struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_request_cell_base (struct regulatory_request*) ; 
 int /*<<< orphan*/  regdom_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum reg_request_treatment
get_reg_request_treatment(struct wiphy *wiphy,
			  struct regulatory_request *pending_request)
{
	struct wiphy *last_wiphy = NULL;
	struct regulatory_request *lr = get_last_request();

	/* All initial requests are respected */
	if (!lr)
		return REG_REQ_OK;

	switch (pending_request->initiator) {
	case NL80211_REGDOM_SET_BY_CORE:
		return REG_REQ_OK;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		if (reg_request_cell_base(lr)) {
			/* Trust a Cell base station over the AP's country IE */
			if (regdom_changes(pending_request->alpha2))
				return REG_REQ_IGNORE;
			return REG_REQ_ALREADY_SET;
		}

		last_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);

		if (unlikely(!is_an_alpha2(pending_request->alpha2)))
			return -EINVAL;
		if (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE) {
			if (last_wiphy != wiphy) {
				/*
				 * Two cards with two APs claiming different
				 * Country IE alpha2s. We could
				 * intersect them, but that seems unlikely
				 * to be correct. Reject second one for now.
				 */
				if (regdom_changes(pending_request->alpha2))
					return REG_REQ_IGNORE;
				return REG_REQ_ALREADY_SET;
			}
			/*
			 * Two consecutive Country IE hints on the same wiphy.
			 * This should be picked up early by the driver/stack
			 */
			if (WARN_ON(regdom_changes(pending_request->alpha2)))
				return REG_REQ_OK;
			return REG_REQ_ALREADY_SET;
		}
		return 0;
	case NL80211_REGDOM_SET_BY_DRIVER:
		if (lr->initiator == NL80211_REGDOM_SET_BY_CORE) {
			if (regdom_changes(pending_request->alpha2))
				return REG_REQ_OK;
			return REG_REQ_ALREADY_SET;
		}

		/*
		 * This would happen if you unplug and plug your card
		 * back in or if you add a new device for which the previously
		 * loaded card also agrees on the regulatory domain.
		 */
		if (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
		    !regdom_changes(pending_request->alpha2))
			return REG_REQ_ALREADY_SET;

		return REG_REQ_INTERSECT;
	case NL80211_REGDOM_SET_BY_USER:
		if (reg_request_cell_base(pending_request))
			return reg_ignore_cell_hint(pending_request);

		if (reg_request_cell_base(lr))
			return REG_REQ_IGNORE;

		if (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE)
			return REG_REQ_INTERSECT;
		/*
		 * If the user knows better the user should set the regdom
		 * to their country before the IE is picked up
		 */
		if (lr->initiator == NL80211_REGDOM_SET_BY_USER &&
		    lr->intersect)
			return REG_REQ_IGNORE;
		/*
		 * Process user requests only after previous user/driver/core
		 * requests have been processed
		 */
		if ((lr->initiator == NL80211_REGDOM_SET_BY_CORE ||
		     lr->initiator == NL80211_REGDOM_SET_BY_DRIVER ||
		     lr->initiator == NL80211_REGDOM_SET_BY_USER) &&
		    regdom_changes(lr->alpha2))
			return REG_REQ_IGNORE;

		if (!regdom_changes(pending_request->alpha2))
			return REG_REQ_ALREADY_SET;

		return REG_REQ_OK;
	}

	return REG_REQ_IGNORE;
}