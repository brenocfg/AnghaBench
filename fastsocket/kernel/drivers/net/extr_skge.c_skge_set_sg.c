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
typedef  scalar_t__ u32 ;
struct skge_port {struct skge_hw* hw; } ;
struct skge_hw {scalar_t__ chip_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 
 int EOPNOTSUPP ; 
 int ethtool_op_set_sg (struct net_device*,scalar_t__) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int skge_set_sg(struct net_device *dev, u32 data)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;

	if (hw->chip_id == CHIP_ID_GENESIS && data)
		return -EOPNOTSUPP;
	return ethtool_op_set_sg(dev, data);
}