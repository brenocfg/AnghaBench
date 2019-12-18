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
struct iw_statistics {int dummy; } ;
struct zd1201 {struct iw_statistics iwstats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct zd1201* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct iw_statistics *zd1201_get_wireless_stats(struct net_device *dev)
{
	struct zd1201 *zd = netdev_priv(dev);

	return &zd->iwstats;
}