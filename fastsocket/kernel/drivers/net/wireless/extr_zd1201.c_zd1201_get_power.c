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
struct zd1201 {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int flags; short value; } ;

/* Variables and functions */
 int IW_POWER_ALL_R ; 
 int IW_POWER_MODE ; 
 int IW_POWER_PERIOD ; 
 int IW_POWER_TIMEOUT ; 
 int IW_POWER_TYPE ; 
 int IW_POWER_UNICAST_R ; 
 int /*<<< orphan*/  ZD1201_RID_CNFMAXSLEEPDURATION ; 
 int /*<<< orphan*/  ZD1201_RID_CNFPMENABLED ; 
 int /*<<< orphan*/  ZD1201_RID_CNFPMEPS ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig16 (struct zd1201*,int /*<<< orphan*/ ,short*) ; 

__attribute__((used)) static int zd1201_get_power(struct net_device *dev,
    struct iw_request_info *info, struct iw_param *vwrq, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	short enabled, level, duration;
	int err;

	err = zd1201_getconfig16(zd, ZD1201_RID_CNFPMENABLED, &enabled);
	if (err)
		return err;
	err = zd1201_getconfig16(zd, ZD1201_RID_CNFPMEPS, &level);
	if (err)
		return err;
	err = zd1201_getconfig16(zd, ZD1201_RID_CNFMAXSLEEPDURATION, &duration);
	if (err)
		return err;
	vwrq->disabled = enabled ? 0 : 1;
	if (vwrq->flags & IW_POWER_TYPE) {
		if (vwrq->flags & IW_POWER_PERIOD) {
			vwrq->value = duration;
			vwrq->flags = IW_POWER_PERIOD;
		} else {
			vwrq->value = duration * level / 4;
			vwrq->flags = IW_POWER_TIMEOUT;
		}
	}
	if (vwrq->flags & IW_POWER_MODE) {
		if (enabled && level)
			vwrq->flags = IW_POWER_UNICAST_R;
		else
			vwrq->flags = IW_POWER_ALL_R;
	}

	return 0;
}