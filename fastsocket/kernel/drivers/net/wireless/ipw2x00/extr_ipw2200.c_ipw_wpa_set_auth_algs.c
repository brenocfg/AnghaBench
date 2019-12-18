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
struct libipw_security {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  flags; } ;
struct libipw_device {int open_wep; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_security ) (int /*<<< orphan*/ ,struct libipw_security*) ;} ;
struct ipw_priv {struct libipw_device* ieee; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_AUTH_ALG_LEAP ; 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
 int /*<<< orphan*/  SEC_AUTH_MODE ; 
 int /*<<< orphan*/  WLAN_AUTH_LEAP ; 
 int /*<<< orphan*/  WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct libipw_security*) ; 

__attribute__((used)) static int ipw_wpa_set_auth_algs(struct ipw_priv *priv, int value)
{
	struct libipw_device *ieee = priv->ieee;
	struct libipw_security sec = {
		.flags = SEC_AUTH_MODE,
	};
	int ret = 0;

	if (value & IW_AUTH_ALG_SHARED_KEY) {
		sec.auth_mode = WLAN_AUTH_SHARED_KEY;
		ieee->open_wep = 0;
	} else if (value & IW_AUTH_ALG_OPEN_SYSTEM) {
		sec.auth_mode = WLAN_AUTH_OPEN;
		ieee->open_wep = 1;
	} else if (value & IW_AUTH_ALG_LEAP) {
		sec.auth_mode = WLAN_AUTH_LEAP;
		ieee->open_wep = 1;
	} else
		return -EINVAL;

	if (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);
	else
		ret = -EOPNOTSUPP;

	return ret;
}