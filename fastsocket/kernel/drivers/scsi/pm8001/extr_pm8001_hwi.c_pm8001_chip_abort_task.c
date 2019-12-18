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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_hba_info {int dummy; } ;
struct pm8001_device {scalar_t__ dev_type; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPC_INB_SATA_ABORT ; 
 int /*<<< orphan*/  OPC_INB_SMP_ABORT ; 
 int /*<<< orphan*/  OPC_INB_SSP_ABORT ; 
 int /*<<< orphan*/  PM8001_EH_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ SAS_END_DEVICE ; 
 scalar_t__ SATA_DEV ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  pm8001_printk (char*,int,...) ; 
 int send_task_abort (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pm8001_chip_abort_task(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_device *pm8001_dev, u8 flag, u32 task_tag, u32 cmd_tag)
{
	u32 opc, device_id;
	int rc = TMF_RESP_FUNC_FAILED;
	PM8001_EH_DBG(pm8001_ha,
		pm8001_printk("cmd_tag = %x, abort task tag = 0x%x",
			cmd_tag, task_tag));
	if (pm8001_dev->dev_type == SAS_END_DEVICE)
		opc = OPC_INB_SSP_ABORT;
	else if (pm8001_dev->dev_type == SATA_DEV)
		opc = OPC_INB_SATA_ABORT;
	else
		opc = OPC_INB_SMP_ABORT;/* SMP */
	device_id = pm8001_dev->device_id;
	rc = send_task_abort(pm8001_ha, opc, device_id, flag,
		task_tag, cmd_tag);
	if (rc != TMF_RESP_FUNC_COMPLETE)
		PM8001_EH_DBG(pm8001_ha, pm8001_printk("rc= %d\n", rc));
	return rc;
}