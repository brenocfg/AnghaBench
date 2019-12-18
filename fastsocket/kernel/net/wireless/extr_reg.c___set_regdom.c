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
struct wiphy {scalar_t__ regd; } ;
struct regulatory_request {scalar_t__ initiator; int /*<<< orphan*/  intersect; int /*<<< orphan*/  wiphy_idx; } ;
struct ieee80211_regdomain {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ieee80211_regdomain const*) ; 
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 scalar_t__ NL80211_REGDOM_SET_BY_DRIVER ; 
 int PTR_ERR (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  get_cfg80211_regdom () ; 
 struct regulatory_request* get_last_request () ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 int /*<<< orphan*/  is_alpha2_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_an_alpha2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_unknown_alpha2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_rd (struct ieee80211_regdomain const*) ; 
 scalar_t__ is_world_regdom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_regdomain_info (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_free_regdom (struct ieee80211_regdomain const*) ; 
 struct ieee80211_regdomain* reg_copy_regd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  reg_is_valid_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_timeout ; 
 int /*<<< orphan*/  regdom_changes (int /*<<< orphan*/ ) ; 
 struct ieee80211_regdomain* regdom_intersect (struct ieee80211_regdomain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_regdomains (int,struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_world_regdomain (struct ieee80211_regdomain const*) ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __set_regdom(const struct ieee80211_regdomain *rd)
{
	const struct ieee80211_regdomain *regd;
	const struct ieee80211_regdomain *intersected_rd = NULL;
	struct wiphy *request_wiphy;
	struct regulatory_request *lr = get_last_request();

	/* Some basic sanity checks first */

	if (!reg_is_valid_request(rd->alpha2))
		return -EINVAL;

	if (is_world_regdom(rd->alpha2)) {
		update_world_regdomain(rd);
		return 0;
	}

	if (!is_alpha2_set(rd->alpha2) && !is_an_alpha2(rd->alpha2) &&
	    !is_unknown_alpha2(rd->alpha2))
		return -EINVAL;

	/*
	 * Lets only bother proceeding on the same alpha2 if the current
	 * rd is non static (it means CRDA was present and was used last)
	 * and the pending request came in from a country IE
	 */
	if (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE) {
		/*
		 * If someone else asked us to change the rd lets only bother
		 * checking if the alpha2 changes if CRDA was already called
		 */
		if (!regdom_changes(rd->alpha2))
			return -EALREADY;
	}

	/*
	 * Now lets set the regulatory domain, update all driver channels
	 * and finally inform them of what we have done, in case they want
	 * to review or adjust their own settings based on their own
	 * internal EEPROM data
	 */

	if (!is_valid_rd(rd)) {
		pr_err("Invalid regulatory domain detected:\n");
		print_regdomain_info(rd);
		return -EINVAL;
	}

	request_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);
	if (!request_wiphy &&
	    (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER ||
	     lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE)) {
		schedule_delayed_work(&reg_timeout, 0);
		return -ENODEV;
	}

	if (!lr->intersect) {
		if (lr->initiator != NL80211_REGDOM_SET_BY_DRIVER) {
			reset_regdomains(false, rd);
			return 0;
		}

		/*
		 * For a driver hint, lets copy the regulatory domain the
		 * driver wanted to the wiphy to deal with conflicts
		 */

		/*
		 * Userspace could have sent two replies with only
		 * one kernel request.
		 */
		if (request_wiphy->regd)
			return -EALREADY;

		regd = reg_copy_regd(rd);
		if (IS_ERR(regd))
			return PTR_ERR(regd);

		rcu_assign_pointer(request_wiphy->regd, regd);
		reset_regdomains(false, rd);
		return 0;
	}

	/* Intersection requires a bit more work */

	if (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE) {
		intersected_rd = regdom_intersect(rd, get_cfg80211_regdom());
		if (!intersected_rd)
			return -EINVAL;

		/*
		 * We can trash what CRDA provided now.
		 * However if a driver requested this specific regulatory
		 * domain we keep it for its private use
		 */
		if (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER) {
			const struct ieee80211_regdomain *tmp;

			tmp = get_wiphy_regdom(request_wiphy);
			rcu_assign_pointer(request_wiphy->regd, rd);
			rcu_free_regdom(tmp);
		} else {
			kfree(rd);
		}

		rd = NULL;

		reset_regdomains(false, intersected_rd);

		return 0;
	}

	return -EINVAL;
}