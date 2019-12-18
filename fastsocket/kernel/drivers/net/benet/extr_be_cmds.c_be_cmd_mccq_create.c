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
struct be_queue_info {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int be_cmd_mccq_ext_create (struct be_adapter*,struct be_queue_info*,struct be_queue_info*) ; 
 int be_cmd_mccq_org_create (struct be_adapter*,struct be_queue_info*,struct be_queue_info*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 

int be_cmd_mccq_create(struct be_adapter *adapter,
			struct be_queue_info *mccq,
			struct be_queue_info *cq)
{
	int status;

	status = be_cmd_mccq_ext_create(adapter, mccq, cq);
	if (status && !lancer_chip(adapter)) {
		dev_warn(&adapter->pdev->dev, "Upgrade to F/W ver 2.102.235.0 "
			"or newer to avoid conflicting priorities between NIC "
			"and FCoE traffic");
		status = be_cmd_mccq_org_create(adapter, mccq, cq);
	}
	return status;
}