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
typedef  scalar_t__ u32 ;
struct qlcnic_hardware_context {int dummy; } ;
struct TYPE_4__ {int* arg; int num; } ;
struct TYPE_3__ {scalar_t__* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CDRP_ARG (int) ; 
 int /*<<< orphan*/  QLCNIC_CDRP_CRB_OFFSET ; 
 scalar_t__ QLCNIC_CDRP_FORM_CMD (scalar_t__) ; 
 int QLCNIC_CDRP_MAX_ARGS ; 
 scalar_t__ QLCNIC_CDRP_RSP_FAIL ; 
 scalar_t__ QLCNIC_CDRP_RSP_OK ; 
 scalar_t__ QLCNIC_CDRP_RSP_TIMEOUT ; 
#define  QLCNIC_RCODE_INVALID 133 
#define  QLCNIC_RCODE_INVALID_ARGS 132 
#define  QLCNIC_RCODE_NOT_IMPL 131 
#define  QLCNIC_RCODE_NOT_PERMITTED 130 
#define  QLCNIC_RCODE_NOT_SUPPORTED 129 
 int QLCNIC_RCODE_SUCCESS ; 
#define  QLCNIC_RCODE_TIMEOUT 128 
 int /*<<< orphan*/  QLCNIC_SIGN_CRB_OFFSET ; 
 void* QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_get_cmd_signature (struct qlcnic_hardware_context*) ; 
 scalar_t__ qlcnic_poll_rsp (struct qlcnic_adapter*) ; 

int qlcnic_82xx_issue_cmd(struct qlcnic_adapter *adapter,
			  struct qlcnic_cmd_args *cmd)
{
	int i;
	u32 rsp;
	u32 signature;
	struct pci_dev *pdev = adapter->pdev;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	signature = qlcnic_get_cmd_signature(ahw);

	/* Acquire semaphore before accessing CRB */
	if (qlcnic_api_lock(adapter)) {
		cmd->rsp.arg[0] = QLCNIC_RCODE_TIMEOUT;
		return cmd->rsp.arg[0];
	}

	QLCWR32(adapter, QLCNIC_SIGN_CRB_OFFSET, signature);
	for (i = 1; i < QLCNIC_CDRP_MAX_ARGS; i++)
		QLCWR32(adapter, QLCNIC_CDRP_ARG(i), cmd->req.arg[i]);
	QLCWR32(adapter, QLCNIC_CDRP_CRB_OFFSET,
		QLCNIC_CDRP_FORM_CMD(cmd->req.arg[0]));
	rsp = qlcnic_poll_rsp(adapter);

	if (rsp == QLCNIC_CDRP_RSP_TIMEOUT) {
		dev_err(&pdev->dev, "card response timeout.\n");
		cmd->rsp.arg[0] = QLCNIC_RCODE_TIMEOUT;
	} else if (rsp == QLCNIC_CDRP_RSP_FAIL) {
		cmd->rsp.arg[0] = QLCRD32(adapter, QLCNIC_CDRP_ARG(1));
		switch (cmd->rsp.arg[0]) {
		case QLCNIC_RCODE_INVALID_ARGS:
			dev_err(&pdev->dev, "CDRP invalid args 0x%x\n",
				cmd->rsp.arg[0]);
			break;
		case QLCNIC_RCODE_NOT_SUPPORTED:
		case QLCNIC_RCODE_NOT_IMPL:
			dev_err(&pdev->dev,
				"CDRP command not supported: 0x%x.\n",
				cmd->rsp.arg[0]);
			break;
		case QLCNIC_RCODE_NOT_PERMITTED:
			dev_err(&pdev->dev,
				"CDRP requested action not permitted: 0x%x.\n",
				cmd->rsp.arg[0]);
			break;
		case QLCNIC_RCODE_INVALID:
			dev_err(&pdev->dev,
				"CDRP invalid or unknown cmd received: 0x%x.\n",
				cmd->rsp.arg[0]);
			break;
		case QLCNIC_RCODE_TIMEOUT:
			dev_err(&pdev->dev, "CDRP command timeout: 0x%x.\n",
				cmd->rsp.arg[0]);
			break;
		default:
			dev_err(&pdev->dev, "CDRP command failed: 0x%x.\n",
				cmd->rsp.arg[0]);
			break;
		}
	} else if (rsp == QLCNIC_CDRP_RSP_OK)
		cmd->rsp.arg[0] = QLCNIC_RCODE_SUCCESS;

	for (i = 1; i < cmd->rsp.num; i++)
		cmd->rsp.arg[i] = QLCRD32(adapter, QLCNIC_CDRP_ARG(i));

	/* Release semaphore */
	qlcnic_api_unlock(adapter);
	return cmd->rsp.arg[0];
}