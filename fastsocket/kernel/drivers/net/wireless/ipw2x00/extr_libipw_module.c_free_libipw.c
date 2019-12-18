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
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct libipw_device {TYPE_1__ wdev; int /*<<< orphan*/  crypt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lib80211_crypt_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libipw_networks_free (struct libipw_device*) ; 
 struct libipw_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 

void free_libipw(struct net_device *dev, int monitor)
{
	struct libipw_device *ieee = netdev_priv(dev);

	lib80211_crypt_info_free(&ieee->crypt_info);

	libipw_networks_free(ieee);

	/* free cfg80211 resources */
	if (!monitor)
		wiphy_free(ieee->wdev.wiphy);

	free_netdev(dev);
}