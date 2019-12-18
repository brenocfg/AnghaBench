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
struct TYPE_2__ {scalar_t__ fixed; int value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ rts; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int rts_threshold; int /*<<< orphan*/  action_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
 int RTS_DISABLED ; 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_rts_threshold (struct ipw2100_priv*,int) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_rts(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int value, err;

	/* Auto RTS not yet supported */
	if (wrqu->rts.fixed == 0)
		return -EINVAL;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (wrqu->rts.disabled)
		value = priv->rts_threshold | RTS_DISABLED;
	else {
		if (wrqu->rts.value < 1 || wrqu->rts.value > 2304) {
			err = -EINVAL;
			goto done;
		}
		value = wrqu->rts.value;
	}

	err = ipw2100_set_rts_threshold(priv, value);

	IPW_DEBUG_WX("SET RTS Threshold -> 0x%08X\n", value);
      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}