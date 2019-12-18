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
struct net_device {int dummy; } ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int ethtool_op_set_tx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 int ethtool_op_set_tx_ipv6_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_set_tx_csum(struct net_device *dev, u32 data)
{
	struct bnx2 *bp = netdev_priv(dev);

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		return (ethtool_op_set_tx_ipv6_csum(dev, data));
	else
		return (ethtool_op_set_tx_csum(dev, data));
}