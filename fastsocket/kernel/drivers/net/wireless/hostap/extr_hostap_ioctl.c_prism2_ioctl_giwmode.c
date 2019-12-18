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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct hostap_interface {int type; TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  iw_mode; } ;
typedef  TYPE_1__ local_info_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
#define  HOSTAP_INTERFACE_STA 129 
#define  HOSTAP_INTERFACE_WDS 128 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_REPEAT ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_giwmode(struct net_device *dev,
				struct iw_request_info *info,
				__u32 *mode, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	switch (iface->type) {
	case HOSTAP_INTERFACE_STA:
		*mode = IW_MODE_INFRA;
		break;
	case HOSTAP_INTERFACE_WDS:
		*mode = IW_MODE_REPEAT;
		break;
	default:
		*mode = local->iw_mode;
		break;
	}
	return 0;
}