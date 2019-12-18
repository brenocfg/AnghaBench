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
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_unregister_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 int /*<<< orphan*/  nl80211_netlink_notifier ; 

void nl80211_exit(void)
{
	netlink_unregister_notifier(&nl80211_netlink_notifier);
	genl_unregister_family(&nl80211_fam);
}