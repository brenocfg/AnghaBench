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
struct net_device {int dummy; } ;
struct be_adapter {int num_vfs; TYPE_2__* vf_cfg; TYPE_1__* pdev; } ;
struct TYPE_4__ {int tx_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int be_cmd_set_profile_config (struct be_adapter*,int,int) ; 
 int be_cmd_set_qos (struct be_adapter*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sriov_enabled (struct be_adapter*) ; 

__attribute__((used)) static int be_set_vf_tx_rate(struct net_device *netdev,
			int vf, int rate)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status = 0;

	if (!sriov_enabled(adapter))
		return -EPERM;

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	if (rate < 100 || rate > 10000) {
		dev_err(&adapter->pdev->dev,
			"tx rate must be between 100 and 10000 Mbps\n");
		return -EINVAL;
	}

	if (lancer_chip(adapter))
		status = be_cmd_set_profile_config(adapter, rate / 10, vf + 1);
	else
		status = be_cmd_set_qos(adapter, rate / 10, vf + 1);

	if (status)
		dev_err(&adapter->pdev->dev,
				"tx rate %d on VF %d failed\n", rate, vf);
	else
		adapter->vf_cfg[vf].tx_rate = rate;
	return status;
}