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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ disabled; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {int fragm_threshold; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {scalar_t__ (* reset_port ) (struct net_device*) ;scalar_t__ (* set_rid ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFA384X_RID_FRAGMENTATIONTHRESHOLD ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub2 (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_siwfrag(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_param *rts, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	__le16 val;

	iface = netdev_priv(dev);
	local = iface->local;

	if (rts->disabled)
		val = cpu_to_le16(2346);
	else if (rts->value < 256 || rts->value > 2346)
		return -EINVAL;
	else
		val = cpu_to_le16(rts->value & ~0x1); /* even numbers only */

	local->fragm_threshold = rts->value & ~0x1;
	if (local->func->set_rid(dev, HFA384X_RID_FRAGMENTATIONTHRESHOLD, &val,
				 2)
	    || local->func->reset_port(dev))
		return -EINVAL;

	return 0;
}