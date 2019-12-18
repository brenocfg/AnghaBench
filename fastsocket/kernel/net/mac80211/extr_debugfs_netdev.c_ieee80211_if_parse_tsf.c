#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; TYPE_1__* ops; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ set_tsf; scalar_t__ reset_tsf; } ;

/* Variables and functions */
 int EINVAL ; 
 int drv_get_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  drv_reset_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  drv_set_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*,unsigned long long) ; 
 int kstrtoull (char const*,int,unsigned long long*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t ieee80211_if_parse_tsf(
	struct ieee80211_sub_if_data *sdata, const char *buf, int buflen)
{
	struct ieee80211_local *local = sdata->local;
	unsigned long long tsf;
	int ret;
	int tsf_is_delta = 0;

	if (strncmp(buf, "reset", 5) == 0) {
		if (local->ops->reset_tsf) {
			drv_reset_tsf(local, sdata);
			wiphy_info(local->hw.wiphy, "debugfs reset TSF\n");
		}
	} else {
		if (buflen > 10 && buf[1] == '=') {
			if (buf[0] == '+')
				tsf_is_delta = 1;
			else if (buf[0] == '-')
				tsf_is_delta = -1;
			else
				return -EINVAL;
			buf += 2;
		}
		ret = kstrtoull(buf, 10, &tsf);
		if (ret < 0)
			return ret;
		if (tsf_is_delta)
			tsf = drv_get_tsf(local, sdata) + tsf_is_delta * tsf;
		if (local->ops->set_tsf) {
			drv_set_tsf(local, sdata, tsf);
			wiphy_info(local->hw.wiphy,
				   "debugfs set TSF to %#018llx\n", tsf);
		}
	}

	return buflen;
}