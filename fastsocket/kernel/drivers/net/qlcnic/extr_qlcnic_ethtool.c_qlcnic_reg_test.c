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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_PCIX_PH_REG (int /*<<< orphan*/ ) ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_reg_test (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_reg_test(struct net_device *dev)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	u32 data_read;

	if (qlcnic_83xx_check(adapter))
		return qlcnic_83xx_reg_test(adapter);

	data_read = QLCRD32(adapter, QLCNIC_PCIX_PH_REG(0));
	if ((data_read & 0xffff) != adapter->pdev->vendor)
		return 1;

	return 0;
}