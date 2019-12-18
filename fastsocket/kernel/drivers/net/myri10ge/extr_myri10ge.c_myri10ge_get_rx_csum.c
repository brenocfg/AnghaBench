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
struct myri10ge_priv {scalar_t__ csum_flag; } ;

/* Variables and functions */
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 myri10ge_get_rx_csum(struct net_device *netdev)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	if (mgp->csum_flag)
		return 1;
	else
		return 0;
}