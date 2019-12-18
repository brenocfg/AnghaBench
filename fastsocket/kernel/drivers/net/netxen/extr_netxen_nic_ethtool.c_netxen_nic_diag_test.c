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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int NETXEN_NIC_TEST_LEN ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netxen_nic_reg_test (struct net_device*) ; 
 scalar_t__ netxen_nic_test_link (struct net_device*) ; 

__attribute__((used)) static void
netxen_nic_diag_test(struct net_device *dev, struct ethtool_test *eth_test,
		     u64 * data)
{
	memset(data, 0, sizeof(uint64_t) * NETXEN_NIC_TEST_LEN);
	if ((data[0] = netxen_nic_reg_test(dev)))
		eth_test->flags |= ETH_TEST_FL_FAILED;
	/* link test */
	if ((data[1] = (u64) netxen_nic_test_link(dev)))
		eth_test->flags |= ETH_TEST_FL_FAILED;
}