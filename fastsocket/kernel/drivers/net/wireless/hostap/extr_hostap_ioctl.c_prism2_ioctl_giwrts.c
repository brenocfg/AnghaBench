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
struct iw_param {int value; int disabled; int fixed; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {scalar_t__ (* get_rid ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFA384X_RID_RTSTHRESHOLD ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int prism2_ioctl_giwrts(struct net_device *dev,
			       struct iw_request_info *info,
			       struct iw_param *rts, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	__le16 val;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->get_rid(dev, HFA384X_RID_RTSTHRESHOLD, &val, 2, 1) <
	    0)
		return -EINVAL;

	rts->value = le16_to_cpu(val);
	rts->disabled = (rts->value == 2347);
	rts->fixed = 1;

	return 0;
}