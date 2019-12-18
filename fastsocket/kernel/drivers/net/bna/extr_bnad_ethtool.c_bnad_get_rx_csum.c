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
struct bnad {int /*<<< orphan*/  rx_csum; } ;

/* Variables and functions */
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32
bnad_get_rx_csum(struct net_device *netdev)
{
	u32 rx_csum;
	struct bnad *bnad = netdev_priv(netdev);

	rx_csum = bnad->rx_csum;
	return rx_csum;
}