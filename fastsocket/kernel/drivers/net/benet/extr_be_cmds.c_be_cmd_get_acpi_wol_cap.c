#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; struct be_cmd_req_acpi_wol_magic_config_v1* va; } ;
struct TYPE_5__ {int response_length; } ;
struct be_cmd_resp_acpi_wol_magic_config_v1 {int /*<<< orphan*/  wol_settings; TYPE_1__ hdr; } ;
struct TYPE_7__ {int version; } ;
struct be_cmd_req_acpi_wol_magic_config_v1 {int /*<<< orphan*/  query_options; TYPE_4__ hdr; } ;
struct be_adapter {TYPE_2__* pdev; int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  wol_cap; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_GET_WOL_CAP ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  OPCODE_ETH_ACPI_WOL_MAGIC_CONFIG ; 
 int /*<<< orphan*/  be_cmd_allowed (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_cmd_req_acpi_wol_magic_config_v1* pci_alloc_consistent (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (TYPE_2__*,int,struct be_cmd_req_acpi_wol_magic_config_v1*,int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_get_acpi_wol_cap(struct be_adapter *adapter)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_acpi_wol_magic_config_v1 *req;
	int status;
	int payload_len = sizeof(*req);
	struct be_dma_mem cmd;

	if (!be_cmd_allowed(adapter, OPCODE_ETH_ACPI_WOL_MAGIC_CONFIG,
			    CMD_SUBSYSTEM_ETH))
		return -EPERM;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	memset(&cmd, 0, sizeof(struct be_dma_mem));
	cmd.size = sizeof(struct be_cmd_resp_acpi_wol_magic_config_v1);
	cmd.va = pci_alloc_consistent(adapter->pdev, cmd.size,
					       &cmd.dma);
	if (!cmd.va) {
		dev_err(&adapter->pdev->dev,
				"Memory allocation failure\n");
		status = -ENOMEM;
		goto err;
	}

	wrb = wrb_from_mbox(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = cmd.va;

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_ACPI_WOL_MAGIC_CONFIG,
			       payload_len, wrb, &cmd);

	req->hdr.version = 1;
	req->query_options = BE_GET_WOL_CAP;

	status = be_mbox_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_acpi_wol_magic_config_v1 *resp;
		resp = (struct be_cmd_resp_acpi_wol_magic_config_v1 *) cmd.va;

		/* the command could succeed misleadingly on old f/w
		 * which is not aware of the V1 version. fake an error. */
		if (resp->hdr.response_length < payload_len) {
			status = -1;
			goto err;
		}
		adapter->wol_cap = resp->wol_settings;
	}
err:
	mutex_unlock(&adapter->mbox_lock);
	if (cmd.va)
		pci_free_consistent(adapter->pdev, cmd.size, cmd.va, cmd.dma);
	return status;

}