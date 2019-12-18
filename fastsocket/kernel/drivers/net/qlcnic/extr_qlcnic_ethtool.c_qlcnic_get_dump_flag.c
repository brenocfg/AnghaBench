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
struct qlcnic_fw_dump {TYPE_2__* tmpl_hdr; int /*<<< orphan*/  enable; scalar_t__ size; scalar_t__ clr; } ;
struct qlcnic_adapter {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  netdev; TYPE_1__* ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int /*<<< orphan*/  version; int /*<<< orphan*/  flag; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  drv_cap_mask; scalar_t__ size; } ;
struct TYPE_3__ {struct qlcnic_fw_dump fw_dump; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
qlcnic_get_dump_flag(struct net_device *netdev, struct ethtool_dump *dump)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;

	if (!fw_dump->tmpl_hdr) {
		netdev_err(adapter->netdev, "FW Dump not supported\n");
		return -ENOTSUPP;
	}

	if (fw_dump->clr)
		dump->len = fw_dump->tmpl_hdr->size + fw_dump->size;
	else
		dump->len = 0;

	if (!fw_dump->enable)
		dump->flag = 0;
	else
		dump->flag = fw_dump->tmpl_hdr->drv_cap_mask;

	dump->version = adapter->fw_version;
	return 0;
}