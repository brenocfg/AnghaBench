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
struct vlan_group {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct bdx_priv {struct vlan_group* vlgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,struct vlan_group*) ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET () ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bdx_vlan_rx_register(struct net_device *ndev, struct vlan_group *grp)
{
	struct bdx_priv *priv = netdev_priv(ndev);

	ENTER;
	DBG("device='%s', group='%p'\n", ndev->name, grp);
	priv->vlgrp = grp;
	RET();
}