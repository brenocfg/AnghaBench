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
typedef  int /*<<< orphan*/  uint32_t ;
struct ql_adapter {int /*<<< orphan*/  rx_csum; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ql_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ql_set_rx_csum(struct net_device *netdev, uint32_t data)
{
	struct ql_adapter *qdev = netdev_priv(netdev);
	qdev->rx_csum = data;
	return 0;
}