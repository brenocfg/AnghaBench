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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct s2io_nic {scalar_t__ bar0; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int len; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsystem_device; } ;

/* Variables and functions */
 int XENA_REG_SPACE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static void s2io_ethtool_gregs(struct net_device *dev,
			       struct ethtool_regs *regs, void *space)
{
	int i;
	u64 reg;
	u8 *reg_space = (u8 *)space;
	struct s2io_nic *sp = netdev_priv(dev);

	regs->len = XENA_REG_SPACE;
	regs->version = sp->pdev->subsystem_device;

	for (i = 0; i < regs->len; i += 8) {
		reg = readq(sp->bar0 + i);
		memcpy((reg_space + i), &reg, 8);
	}
}