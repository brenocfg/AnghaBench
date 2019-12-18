#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_csum; } ;
struct spider_net_card {TYPE_1__ options; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct spider_net_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32
spider_net_ethtool_get_rx_csum(struct net_device *netdev)
{
	struct spider_net_card *card = netdev_priv(netdev);

	return card->options.rx_csum;
}