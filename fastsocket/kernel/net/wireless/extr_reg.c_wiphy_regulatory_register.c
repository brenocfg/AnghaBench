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

/* Variables and functions */
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_CORE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_dev_ignore_cell_hint (struct wiphy*) ; 
 int /*<<< orphan*/  reg_mutex ; 
 int /*<<< orphan*/  reg_num_devs_support_basehint ; 
 int /*<<< orphan*/  wiphy_update_regulatory (struct wiphy*,int /*<<< orphan*/ ) ; 

void wiphy_regulatory_register(struct wiphy *wiphy)
{
	mutex_lock(&reg_mutex);

	if (!reg_dev_ignore_cell_hint(wiphy))
		reg_num_devs_support_basehint++;

	wiphy_update_regulatory(wiphy, NL80211_REGDOM_SET_BY_CORE);

	mutex_unlock(&reg_mutex);
}