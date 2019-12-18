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
struct iw_param {long flags; int /*<<< orphan*/  value; } ;
union iwreq_data {struct iw_param param; } ;
struct orinoco_private {int /*<<< orphan*/  wpa_enabled; int /*<<< orphan*/  wep_restrict; int /*<<< orphan*/  tkip_cm_active; int /*<<< orphan*/  key_mgmt; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 131 
 int /*<<< orphan*/  IW_AUTH_ALG_OPEN_SYSTEM ; 
 int /*<<< orphan*/  IW_AUTH_ALG_SHARED_KEY ; 
 long IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 130 
#define  IW_AUTH_TKIP_COUNTERMEASURES 129 
#define  IW_AUTH_WPA_ENABLED 128 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_get_auth(struct net_device *dev,
				  struct iw_request_info *info,
				  union iwreq_data *wrqu, char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct iw_param *param = &wrqu->param;
	unsigned long flags;
	int ret = 0;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_KEY_MGMT:
		param->value = priv->key_mgmt;
		break;

	case IW_AUTH_TKIP_COUNTERMEASURES:
		param->value = priv->tkip_cm_active;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		if (priv->wep_restrict)
			param->value = IW_AUTH_ALG_SHARED_KEY;
		else
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = priv->wpa_enabled;
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	orinoco_unlock(priv, &flags);
	return ret;
}