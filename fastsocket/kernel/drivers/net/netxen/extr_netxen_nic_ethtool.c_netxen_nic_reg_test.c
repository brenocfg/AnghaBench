#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_2__ ahw; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_SCRATCHPAD_TEST ; 
 int /*<<< orphan*/  NETXEN_PCIX_PH_REG (int /*<<< orphan*/ ) ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netxen_nic_reg_test(struct net_device *dev)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u32 data_read, data_written;

	data_read = NXRD32(adapter, NETXEN_PCIX_PH_REG(0));
	if ((data_read & 0xffff) != adapter->pdev->vendor)
		return 1;

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		return 0;

	data_written = (u32)0xa5a5a5a5;

	NXWR32(adapter, CRB_SCRATCHPAD_TEST, data_written);
	data_read = NXRD32(adapter, CRB_SCRATCHPAD_TEST);
	if (data_written != data_read)
		return 1;

	return 0;
}