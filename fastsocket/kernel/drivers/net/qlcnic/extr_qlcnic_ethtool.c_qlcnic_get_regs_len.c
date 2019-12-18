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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  ext_diag_registers ;
typedef  int /*<<< orphan*/  diag_registers ;

/* Variables and functions */
 int QLCNIC_DEV_INFO_SIZE ; 
 int QLCNIC_RING_REGS_LEN ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_get_regs_len (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_get_regs_len(struct net_device *dev)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	u32 len;

	if (qlcnic_83xx_check(adapter))
		len = qlcnic_83xx_get_regs_len(adapter);
	else
		len = sizeof(ext_diag_registers) + sizeof(diag_registers);

	return QLCNIC_RING_REGS_LEN + len + QLCNIC_DEV_INFO_SIZE + 1;
}