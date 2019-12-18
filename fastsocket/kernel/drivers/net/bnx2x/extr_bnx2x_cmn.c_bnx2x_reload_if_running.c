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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_NORMAL ; 
 int /*<<< orphan*/  UNLOAD_NORMAL ; 
 int bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_nic_unload (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

int bnx2x_reload_if_running(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);

	if (unlikely(!netif_running(dev)))
		return 0;

	bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
	return bnx2x_nic_load(bp, LOAD_NORMAL);
}