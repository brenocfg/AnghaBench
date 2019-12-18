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
struct qlcnic_adapter {scalar_t__ is_up; struct pci_dev* pdev; struct net_device* netdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_alloc_hw_resources (struct qlcnic_adapter*) ; 
 int qlcnic_alloc_sw_resources (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_create_sysfs_entries (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_hw_resources (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_sw_resources (struct qlcnic_adapter*) ; 
 int qlcnic_napi_add (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_napi_del (struct qlcnic_adapter*) ; 
 int qlcnic_request_irq (struct qlcnic_adapter*) ; 

int
qlcnic_attach(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	int err;

	if (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC)
		return 0;

	err = qlcnic_napi_add(adapter, netdev);
	if (err)
		return err;

	err = qlcnic_alloc_sw_resources(adapter);
	if (err) {
		dev_err(&pdev->dev, "Error in setting sw resources\n");
		goto err_out_napi_del;
	}

	err = qlcnic_alloc_hw_resources(adapter);
	if (err) {
		dev_err(&pdev->dev, "Error in setting hw resources\n");
		goto err_out_free_sw;
	}

	err = qlcnic_request_irq(adapter);
	if (err) {
		dev_err(&pdev->dev, "failed to setup interrupt\n");
		goto err_out_free_hw;
	}

	qlcnic_create_sysfs_entries(adapter);

	adapter->is_up = QLCNIC_ADAPTER_UP_MAGIC;
	return 0;

err_out_free_hw:
	qlcnic_free_hw_resources(adapter);
err_out_free_sw:
	qlcnic_free_sw_resources(adapter);
err_out_napi_del:
	qlcnic_napi_del(adapter);
	return err;
}