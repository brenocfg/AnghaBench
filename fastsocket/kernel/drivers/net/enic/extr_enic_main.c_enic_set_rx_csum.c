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
struct net_device {int dummy; } ;
struct enic {int csum_rx_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENIC_SETTING (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXCSUM ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_set_rx_csum(struct net_device *netdev, u32 data)
{
	struct enic *enic = netdev_priv(netdev);

	if (data && !ENIC_SETTING(enic, RXCSUM))
		return -EINVAL;

	enic->csum_rx_enabled = !!data;

	return 0;
}