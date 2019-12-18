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
struct ieee80211_sub_if_data {int dummy; } ;
typedef  int ssize_t ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_SMPS_NUM_MODES ; 
 int ieee80211_set_smps (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/ * smps_modes ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t ieee80211_if_parse_smps(struct ieee80211_sub_if_data *sdata,
				       const char *buf, int buflen)
{
	enum ieee80211_smps_mode mode;

	for (mode = 0; mode < IEEE80211_SMPS_NUM_MODES; mode++) {
		if (strncmp(buf, smps_modes[mode], buflen) == 0) {
			int err = ieee80211_set_smps(sdata, mode);
			if (!err)
				return buflen;
			return err;
		}
	}

	return -EINVAL;
}