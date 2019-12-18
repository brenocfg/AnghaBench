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
struct wiphy {int /*<<< orphan*/  regd; } ;
struct regulatory_request {int /*<<< orphan*/  country_ie_env; int /*<<< orphan*/  wiphy_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVIRON_ANY ; 
 int /*<<< orphan*/  WIPHY_IDX_INVALID ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  get_wiphy_regdom (struct wiphy*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_free_regdom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_dev_ignore_cell_hint (struct wiphy*) ; 
 int /*<<< orphan*/  reg_mutex ; 
 int /*<<< orphan*/  reg_num_devs_support_basehint ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

void wiphy_regulatory_deregister(struct wiphy *wiphy)
{
	struct wiphy *request_wiphy = NULL;
	struct regulatory_request *lr;

	mutex_lock(&reg_mutex);
	lr = get_last_request();

	if (!reg_dev_ignore_cell_hint(wiphy))
		reg_num_devs_support_basehint--;

	rcu_free_regdom(get_wiphy_regdom(wiphy));
	rcu_assign_pointer(wiphy->regd, NULL);

	if (lr)
		request_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);

	if (!request_wiphy || request_wiphy != wiphy)
		goto out;

	lr->wiphy_idx = WIPHY_IDX_INVALID;
	lr->country_ie_env = ENVIRON_ANY;
out:
	mutex_unlock(&reg_mutex);
}