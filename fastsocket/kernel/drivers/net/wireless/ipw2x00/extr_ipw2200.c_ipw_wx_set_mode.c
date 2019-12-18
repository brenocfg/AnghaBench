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
union iwreq_data {int mode; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  adapter_restart; TYPE_2__* ieee; TYPE_1__* net_dev; } ;
struct TYPE_4__ {int iw_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
#define  IW_MODE_ADHOC 131 
#define  IW_MODE_AUTO 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MONITOR 128 
 int /*<<< orphan*/  free_firmware () ; 
 int /*<<< orphan*/  ipw_sw_reset (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_mode(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int err = 0;

	IPW_DEBUG_WX("Set MODE: %d\n", wrqu->mode);

	switch (wrqu->mode) {
#ifdef CONFIG_IPW2200_MONITOR
	case IW_MODE_MONITOR:
#endif
	case IW_MODE_ADHOC:
	case IW_MODE_INFRA:
		break;
	case IW_MODE_AUTO:
		wrqu->mode = IW_MODE_INFRA;
		break;
	default:
		return -EINVAL;
	}
	if (wrqu->mode == priv->ieee->iw_mode)
		return 0;

	mutex_lock(&priv->mutex);

	ipw_sw_reset(priv, 0);

#ifdef CONFIG_IPW2200_MONITOR
	if (priv->ieee->iw_mode == IW_MODE_MONITOR)
		priv->net_dev->type = ARPHRD_ETHER;

	if (wrqu->mode == IW_MODE_MONITOR)
#ifdef CONFIG_IPW2200_RADIOTAP
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
#else
		priv->net_dev->type = ARPHRD_IEEE80211;
#endif
#endif				/* CONFIG_IPW2200_MONITOR */

	/* Free the existing firmware and reset the fw_loaded
	 * flag so ipw_load() will bring in the new firmware */
	free_firmware();

	priv->ieee->iw_mode = wrqu->mode;

	schedule_work(&priv->adapter_restart);
	mutex_unlock(&priv->mutex);
	return err;
}