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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int genl_register_family_with_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genl_register_mc_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ *) ; 
 int netlink_register_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_config_mcgrp ; 
 int /*<<< orphan*/  nl80211_fam ; 
 int /*<<< orphan*/  nl80211_mlme_mcgrp ; 
 int /*<<< orphan*/  nl80211_netlink_notifier ; 
 int /*<<< orphan*/  nl80211_ops ; 
 int /*<<< orphan*/  nl80211_regulatory_mcgrp ; 
 int /*<<< orphan*/  nl80211_scan_mcgrp ; 
 int /*<<< orphan*/  nl80211_testmode_mcgrp ; 

int nl80211_init(void)
{
	int err;

	err = genl_register_family_with_ops(&nl80211_fam,
		nl80211_ops, ARRAY_SIZE(nl80211_ops));
	if (err)
		return err;

	err = genl_register_mc_group(&nl80211_fam, &nl80211_config_mcgrp);
	if (err)
		goto err_out;

	err = genl_register_mc_group(&nl80211_fam, &nl80211_scan_mcgrp);
	if (err)
		goto err_out;

	err = genl_register_mc_group(&nl80211_fam, &nl80211_regulatory_mcgrp);
	if (err)
		goto err_out;

	err = genl_register_mc_group(&nl80211_fam, &nl80211_mlme_mcgrp);
	if (err)
		goto err_out;

#ifdef CONFIG_NL80211_TESTMODE
	err = genl_register_mc_group(&nl80211_fam, &nl80211_testmode_mcgrp);
	if (err)
		goto err_out;
#endif

	err = netlink_register_notifier(&nl80211_netlink_notifier);
	if (err)
		goto err_out;

	return 0;
 err_out:
	genl_unregister_family(&nl80211_fam);
	return err;
}