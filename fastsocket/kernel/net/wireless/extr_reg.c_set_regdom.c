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
struct regulatory_request {int /*<<< orphan*/  initiator; int /*<<< orphan*/  intersect; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int __set_regdom (struct ieee80211_regdomain const*) ; 
 struct ieee80211_regdomain const* get_cfg80211_regdom () ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_send_reg_change_event (struct regulatory_request*) ; 
 int /*<<< orphan*/  print_regdomain (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  reg_mutex ; 
 int /*<<< orphan*/  reg_set_request_processed () ; 
 int /*<<< orphan*/  update_all_wiphy_regulatory (int /*<<< orphan*/ ) ; 

int set_regdom(const struct ieee80211_regdomain *rd)
{
	struct regulatory_request *lr;
	int r;

	mutex_lock(&reg_mutex);
	lr = get_last_request();

	/* Note that this doesn't update the wiphys, this is done below */
	r = __set_regdom(rd);
	if (r) {
		if (r == -EALREADY)
			reg_set_request_processed();

		kfree(rd);
		goto out;
	}

	/* This would make this whole thing pointless */
	if (WARN_ON(!lr->intersect && rd != get_cfg80211_regdom())) {
		r = -EINVAL;
		goto out;
	}

	/* update all wiphys now with the new established regulatory domain */
	update_all_wiphy_regulatory(lr->initiator);

	print_regdomain(get_cfg80211_regdom());

	nl80211_send_reg_change_event(lr);

	reg_set_request_processed();

 out:
	mutex_unlock(&reg_mutex);

	return r;
}