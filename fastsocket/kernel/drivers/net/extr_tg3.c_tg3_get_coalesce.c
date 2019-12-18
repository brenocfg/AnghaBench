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
struct tg3 {int /*<<< orphan*/  coal; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ethtool_coalesce*,int /*<<< orphan*/ *,int) ; 
 struct tg3* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int tg3_get_coalesce(struct net_device *dev, struct ethtool_coalesce *ec)
{
	struct tg3 *tp = netdev_priv(dev);

	memcpy(ec, &tp->coal, sizeof(*ec));
	return 0;
}