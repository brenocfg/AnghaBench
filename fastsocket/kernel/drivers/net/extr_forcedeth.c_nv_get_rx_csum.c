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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct fe_priv {scalar_t__ rx_csum; } ;

/* Variables and functions */
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 nv_get_rx_csum(struct net_device *dev)
{
	struct fe_priv *np = netdev_priv(dev);
	return (np->rx_csum) != 0;
}