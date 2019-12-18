#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num; int /*<<< orphan*/ * arg; } ;
struct TYPE_4__ {int num; int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void qlcnic_dump_mbx(struct qlcnic_adapter *adapter,
			    struct qlcnic_cmd_args *cmd)
{
	int i;

	dev_info(&adapter->pdev->dev,
		 "Host MBX regs(%d)\n", cmd->req.num);
	for (i = 0; i < cmd->req.num; i++) {
		if (i && !(i % 8))
			pr_info("\n");
		pr_info("%08x ", cmd->req.arg[i]);
	}
	pr_info("\n");
	dev_info(&adapter->pdev->dev,
		 "FW MBX regs(%d)\n", cmd->rsp.num);
	for (i = 0; i < cmd->rsp.num; i++) {
		if (i && !(i % 8))
			pr_info("\n");
		pr_info("%08x ", cmd->rsp.arg[i]);
	}
	pr_info("\n");
}