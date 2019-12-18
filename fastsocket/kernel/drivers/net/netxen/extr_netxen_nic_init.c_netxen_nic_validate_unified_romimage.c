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
struct netxen_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ netxen_nic_validate_bootld (struct netxen_adapter*) ; 
 scalar_t__ netxen_nic_validate_fw (struct netxen_adapter*) ; 
 scalar_t__ netxen_nic_validate_header (struct netxen_adapter*) ; 
 scalar_t__ netxen_nic_validate_product_offs (struct netxen_adapter*) ; 

__attribute__((used)) static int
netxen_nic_validate_unified_romimage(struct netxen_adapter *adapter)
{
	if (netxen_nic_validate_header(adapter)) {
		dev_err(&adapter->pdev->dev,
				"unified image: header validation failed\n");
		return -EINVAL;
	}

	if (netxen_nic_validate_product_offs(adapter)) {
		dev_err(&adapter->pdev->dev,
				"unified image: product validation failed\n");
		return -EINVAL;
	}

	if (netxen_nic_validate_bootld(adapter)) {
		dev_err(&adapter->pdev->dev,
				"unified image: bootld validation failed\n");
		return -EINVAL;
	}

	if (netxen_nic_validate_fw(adapter)) {
		dev_err(&adapter->pdev->dev,
				"unified image: firmware validation failed\n");
		return -EINVAL;
	}

	return 0;
}