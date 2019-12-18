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
struct net_device {int dummy; } ;

/* Variables and functions */
 int NES_ETHTOOL_STAT_COUNT ; 

__attribute__((used)) static int nes_netdev_get_stats_count(struct net_device *netdev)
{
	return NES_ETHTOOL_STAT_COUNT;
}