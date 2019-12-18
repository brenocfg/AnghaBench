#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {int dummy; } ;
struct TYPE_4__ {struct net_device_stats linux_stats; } ;
typedef  TYPE_1__ wlandevice_t ;
struct TYPE_5__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */

__attribute__((used)) static struct net_device_stats *p80211knetdev_get_stats(netdevice_t * netdev)
{
	wlandevice_t *wlandev = netdev->ml_priv;

	/* TODO: review the MIB stats for items that correspond to
	   linux stats */

	return &(wlandev->linux_stats);
}