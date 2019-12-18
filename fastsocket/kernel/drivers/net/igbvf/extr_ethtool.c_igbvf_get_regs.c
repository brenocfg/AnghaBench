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
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {TYPE_1__* pdev; struct e1000_hw hw; } ;
struct ethtool_regs {int version; } ;
struct TYPE_2__ {int revision; int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int IGBVF_REGS_LEN ; 
 int /*<<< orphan*/  RDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igbvf_get_regs(struct net_device *netdev,
                           struct ethtool_regs *regs, void *p)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;

	memset(p, 0, IGBVF_REGS_LEN * sizeof(u32));

	regs->version = (1 << 24) | (adapter->pdev->revision << 16) |
			adapter->pdev->device;

	regs_buff[0] = er32(CTRL);
	regs_buff[1] = er32(STATUS);

	regs_buff[2] = er32(RDLEN(0));
	regs_buff[3] = er32(RDH(0));
	regs_buff[4] = er32(RDT(0));

	regs_buff[5] = er32(TDLEN(0));
	regs_buff[6] = er32(TDH(0));
	regs_buff[7] = er32(TDT(0));
}