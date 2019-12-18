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
struct ieee80211_security {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  flags; } ;
struct ieee80211_device {int open_wep; int auth_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_security ) (int /*<<< orphan*/ ,struct ieee80211_security*) ;} ;

/* Variables and functions */
 int AUTH_ALG_LEAP ; 
 int AUTH_ALG_OPEN_SYSTEM ; 
 int AUTH_ALG_SHARED_KEY ; 
 int /*<<< orphan*/  RTL_WLAN_AUTH_LEAP ; 
 int /*<<< orphan*/  SEC_AUTH_MODE ; 
 int /*<<< orphan*/  WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_security*) ; 

__attribute__((used)) static int ieee80211_wpa_set_auth_algs(struct ieee80211_device *ieee, int value)
{

	struct ieee80211_security sec = {
		.flags = SEC_AUTH_MODE,
	};
	int ret = 0;

	if (value & AUTH_ALG_SHARED_KEY) {
		sec.auth_mode = WLAN_AUTH_SHARED_KEY;
		ieee->open_wep = 0;
		ieee->auth_mode = 1;
	} else if (value & AUTH_ALG_OPEN_SYSTEM){
		sec.auth_mode = WLAN_AUTH_OPEN;
		ieee->open_wep = 1;
		ieee->auth_mode = 0;
	}
	else if (value & AUTH_ALG_LEAP){
		sec.auth_mode = RTL_WLAN_AUTH_LEAP;
		ieee->open_wep = 1;
		ieee->auth_mode = 2;
	}


	if (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);
	//else
	//	ret = -EOPNOTSUPP;

	return ret;
}