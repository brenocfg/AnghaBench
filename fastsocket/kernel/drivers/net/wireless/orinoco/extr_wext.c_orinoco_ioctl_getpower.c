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
typedef  int u16 ;
struct hermes {int dummy; } ;
struct orinoco_private {struct hermes hw; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int flags; int value; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HERMES_RID_CNFMAXSLEEPDURATION ; 
 int /*<<< orphan*/  HERMES_RID_CNFMULTICASTRECEIVE ; 
 int /*<<< orphan*/  HERMES_RID_CNFPMENABLED ; 
 int /*<<< orphan*/  HERMES_RID_CNFPMHOLDOVERDURATION ; 
 int IW_POWER_ALL_R ; 
 int IW_POWER_PERIOD ; 
 int IW_POWER_TIMEOUT ; 
 int IW_POWER_TYPE ; 
 int IW_POWER_UNICAST_R ; 
 int /*<<< orphan*/  USER_BAP ; 
 int hermes_read_wordrec (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_getpower(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_param *prq,
				  char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct hermes *hw = &priv->hw;
	int err = 0;
	u16 enable, period, timeout, mcast;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = hermes_read_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFPMENABLED, &enable);
	if (err)
		goto out;

	err = hermes_read_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFMAXSLEEPDURATION, &period);
	if (err)
		goto out;

	err = hermes_read_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFPMHOLDOVERDURATION, &timeout);
	if (err)
		goto out;

	err = hermes_read_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFMULTICASTRECEIVE, &mcast);
	if (err)
		goto out;

	prq->disabled = !enable;
	/* Note : by default, display the period */
	if ((prq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) {
		prq->flags = IW_POWER_TIMEOUT;
		prq->value = timeout * 1000;
	} else {
		prq->flags = IW_POWER_PERIOD;
		prq->value = period * 1000;
	}
	if (mcast)
		prq->flags |= IW_POWER_ALL_R;
	else
		prq->flags |= IW_POWER_UNICAST_R;

 out:
	orinoco_unlock(priv, &flags);

	return err;
}