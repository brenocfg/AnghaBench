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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int m; int e; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_3__ {scalar_t__ (* get_rid ) (struct net_device*,int /*<<< orphan*/ ,int*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_COUNT ; 
 int /*<<< orphan*/  HFA384X_RID_CURRENTCHANNEL ; 
 int* freq_list ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int prism2_ioctl_giwfreq(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_freq *freq, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	u16 val;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->get_rid(dev, HFA384X_RID_CURRENTCHANNEL, &val, 2, 1) <
	    0)
		return -EINVAL;

	le16_to_cpus(&val);
	if (val < 1 || val > FREQ_COUNT)
		return -EINVAL;

	freq->m = freq_list[val - 1] * 100000;
	freq->e = 1;

	return 0;
}