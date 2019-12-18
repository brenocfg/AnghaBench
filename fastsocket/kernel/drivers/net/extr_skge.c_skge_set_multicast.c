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
struct skge_port {struct skge_hw* hw; } ;
struct skge_hw {scalar_t__ chip_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 
 int /*<<< orphan*/  genesis_set_multicast (struct net_device*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  yukon_set_multicast (struct net_device*) ; 

__attribute__((used)) static void skge_set_multicast(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;

	if (hw->chip_id == CHIP_ID_GENESIS)
		genesis_set_multicast(dev);
	else
		yukon_set_multicast(dev);

}