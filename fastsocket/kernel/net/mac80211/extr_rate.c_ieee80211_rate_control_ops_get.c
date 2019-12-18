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
struct rate_control_ops {int dummy; } ;

/* Variables and functions */
 char const* CONFIG_MAC80211_RC_DEFAULT ; 
 char const* ieee80211_default_rc_algo ; 
 struct rate_control_ops* ieee80211_try_rate_control_ops_get (char const*) ; 
 int /*<<< orphan*/  kparam_block_sysfs_write (char const*) ; 
 int /*<<< orphan*/  kparam_unblock_sysfs_write (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct rate_control_ops *
ieee80211_rate_control_ops_get(const char *name)
{
	struct rate_control_ops *ops;
	const char *alg_name;

	kparam_block_sysfs_write(ieee80211_default_rc_algo);
	if (!name)
		alg_name = ieee80211_default_rc_algo;
	else
		alg_name = name;

	ops = ieee80211_try_rate_control_ops_get(alg_name);
	if (!ops) {
		request_module("rc80211_%s", alg_name);
		ops = ieee80211_try_rate_control_ops_get(alg_name);
	}
	if (!ops && name)
		/* try default if specific alg requested but not found */
		ops = ieee80211_try_rate_control_ops_get(ieee80211_default_rc_algo);

	/* try built-in one if specific alg requested but not found */
	if (!ops && strlen(CONFIG_MAC80211_RC_DEFAULT))
		ops = ieee80211_try_rate_control_ops_get(CONFIG_MAC80211_RC_DEFAULT);
	kparam_unblock_sysfs_write(ieee80211_default_rc_algo);

	return ops;
}