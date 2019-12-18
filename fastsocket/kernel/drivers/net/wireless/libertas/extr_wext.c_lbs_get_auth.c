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
struct net_device {struct lbs_private* ml_priv; } ;
struct TYPE_2__ {int key_mgmt; int auth_mode; int /*<<< orphan*/  WPA2enabled; int /*<<< orphan*/  WPAenabled; } ;
struct lbs_private {TYPE_1__ secinfo; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 131 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int IW_AUTH_WPA_VERSION_DISABLED ; 
 int IW_AUTH_WPA_VERSION_WPA ; 
 int IW_AUTH_WPA_VERSION_WPA2 ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int lbs_get_auth(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_param *dwrq,
			 char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	switch (dwrq->flags & IW_AUTH_INDEX) {
	case IW_AUTH_KEY_MGMT:
		dwrq->value = priv->secinfo.key_mgmt;
		break;

	case IW_AUTH_WPA_VERSION:
		dwrq->value = 0;
		if (priv->secinfo.WPAenabled)
			dwrq->value |= IW_AUTH_WPA_VERSION_WPA;
		if (priv->secinfo.WPA2enabled)
			dwrq->value |= IW_AUTH_WPA_VERSION_WPA2;
		if (!dwrq->value)
			dwrq->value |= IW_AUTH_WPA_VERSION_DISABLED;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		dwrq->value = priv->secinfo.auth_mode;
		break;

	case IW_AUTH_WPA_ENABLED:
		if (priv->secinfo.WPAenabled && priv->secinfo.WPA2enabled)
			dwrq->value = 1;
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}