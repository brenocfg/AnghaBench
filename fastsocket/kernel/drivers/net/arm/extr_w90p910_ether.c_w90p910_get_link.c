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
typedef  int /*<<< orphan*/  u32 ;
struct w90p910_ether {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_link_ok (int /*<<< orphan*/ *) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 w90p910_get_link(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	return mii_link_ok(&ether->mii);
}