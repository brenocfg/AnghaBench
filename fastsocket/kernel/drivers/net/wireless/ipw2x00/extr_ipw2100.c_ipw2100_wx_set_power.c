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
struct TYPE_2__ {int flags; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ power; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int power_mode; int /*<<< orphan*/  action_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int IPW_POWER_ENABLED ; 
 int IPW_POWER_LEVEL (int) ; 
 int IPW_POWER_MODE_CAM ; 
#define  IW_POWER_ALL_R 130 
#define  IW_POWER_MODE 129 
#define  IW_POWER_ON 128 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_power_mode (struct ipw2100_priv*,int) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_power(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (wrqu->power.disabled) {
		priv->power_mode = IPW_POWER_LEVEL(priv->power_mode);
		err = ipw2100_set_power_mode(priv, IPW_POWER_MODE_CAM);
		IPW_DEBUG_WX("SET Power Management Mode -> off\n");
		goto done;
	}

	switch (wrqu->power.flags & IW_POWER_MODE) {
	case IW_POWER_ON:	/* If not specified */
	case IW_POWER_MODE:	/* If set all mask */
	case IW_POWER_ALL_R:	/* If explicitly state all */
		break;
	default:		/* Otherwise we don't support it */
		IPW_DEBUG_WX("SET PM Mode: %X not supported.\n",
			     wrqu->power.flags);
		err = -EOPNOTSUPP;
		goto done;
	}

	/* If the user hasn't specified a power management mode yet, default
	 * to BATTERY */
	priv->power_mode = IPW_POWER_ENABLED | priv->power_mode;
	err = ipw2100_set_power_mode(priv, IPW_POWER_LEVEL(priv->power_mode));

	IPW_DEBUG_WX("SET Power Management Mode -> 0x%02X\n", priv->power_mode);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;

}