#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int features; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
typedef  enum nl80211_commands { ____Placeholder_nl80211_commands } nl80211_commands ;
typedef  enum nl80211_auth_type { ____Placeholder_nl80211_auth_type } nl80211_auth_type ;

/* Variables and functions */
 int NL80211_AUTHTYPE_MAX ; 
 int NL80211_AUTHTYPE_SAE ; 
#define  NL80211_CMD_AUTHENTICATE 130 
#define  NL80211_CMD_CONNECT 129 
#define  NL80211_CMD_START_AP 128 
 int NL80211_FEATURE_SAE ; 

__attribute__((used)) static bool nl80211_valid_auth_type(struct cfg80211_registered_device *rdev,
				    enum nl80211_auth_type auth_type,
				    enum nl80211_commands cmd)
{
	if (auth_type > NL80211_AUTHTYPE_MAX)
		return false;

	switch (cmd) {
	case NL80211_CMD_AUTHENTICATE:
		if (!(rdev->wiphy.features & NL80211_FEATURE_SAE) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			return false;
		return true;
	case NL80211_CMD_CONNECT:
	case NL80211_CMD_START_AP:
		/* SAE not supported yet */
		if (auth_type == NL80211_AUTHTYPE_SAE)
			return false;
		return true;
	default:
		return false;
	}
}