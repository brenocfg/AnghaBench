#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myri10ge_priv {int num_slices; char* fw_name; int max_intr_slots; TYPE_1__* msix_vectors; struct pci_dev* pdev; } ;
struct myri10ge_cmd {int data0; } ;
struct mcp_slot {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MXGEFW_CMD_GET_MAX_RSS_QUEUES ; 
 int /*<<< orphan*/  MXGEFW_CMD_RESET ; 
 int /*<<< orphan*/  MXGEFW_CMD_SET_INTRQ_SIZE ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct myri10ge_cmd*,int /*<<< orphan*/ ,int) ; 
 char* myri10ge_fw_aligned ; 
 char* myri10ge_fw_name ; 
 char* myri10ge_fw_rss_aligned ; 
 char* myri10ge_fw_rss_unaligned ; 
 int myri10ge_load_firmware (struct myri10ge_priv*,int /*<<< orphan*/ ) ; 
 int myri10ge_max_slices ; 
 int /*<<< orphan*/  myri10ge_msi ; 
 int myri10ge_send_cmd (struct myri10ge_priv*,int /*<<< orphan*/ ,struct myri10ge_cmd*,int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int pci_enable_msix (struct pci_dev*,TYPE_1__*,int) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myri10ge_probe_slices(struct myri10ge_priv *mgp)
{
	struct myri10ge_cmd cmd;
	struct pci_dev *pdev = mgp->pdev;
	char *old_fw;
	int i, status, ncpus, msix_cap;

	mgp->num_slices = 1;
	msix_cap = pci_find_capability(pdev, PCI_CAP_ID_MSIX);
	ncpus = num_online_cpus();

	if (myri10ge_max_slices == 1 || msix_cap == 0 ||
	    (myri10ge_max_slices == -1 && ncpus < 2))
		return;

	/* try to load the slice aware rss firmware */
	old_fw = mgp->fw_name;
	if (myri10ge_fw_name != NULL) {
		dev_info(&mgp->pdev->dev, "overriding rss firmware to %s\n",
			 myri10ge_fw_name);
		mgp->fw_name = myri10ge_fw_name;
	} else if (old_fw == myri10ge_fw_aligned)
		mgp->fw_name = myri10ge_fw_rss_aligned;
	else
		mgp->fw_name = myri10ge_fw_rss_unaligned;
	status = myri10ge_load_firmware(mgp, 0);
	if (status != 0) {
		dev_info(&pdev->dev, "Rss firmware not found\n");
		return;
	}

	/* hit the board with a reset to ensure it is alive */
	memset(&cmd, 0, sizeof(cmd));
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_RESET, &cmd, 0);
	if (status != 0) {
		dev_err(&mgp->pdev->dev, "failed reset\n");
		goto abort_with_fw;
		return;
	}

	mgp->max_intr_slots = cmd.data0 / sizeof(struct mcp_slot);

	/* tell it the size of the interrupt queues */
	cmd.data0 = mgp->max_intr_slots * sizeof(struct mcp_slot);
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_SET_INTRQ_SIZE, &cmd, 0);
	if (status != 0) {
		dev_err(&mgp->pdev->dev, "failed MXGEFW_CMD_SET_INTRQ_SIZE\n");
		goto abort_with_fw;
	}

	/* ask the maximum number of slices it supports */
	status = myri10ge_send_cmd(mgp, MXGEFW_CMD_GET_MAX_RSS_QUEUES, &cmd, 0);
	if (status != 0)
		goto abort_with_fw;
	else
		mgp->num_slices = cmd.data0;

	/* Only allow multiple slices if MSI-X is usable */
	if (!myri10ge_msi) {
		goto abort_with_fw;
	}

	/* if the admin did not specify a limit to how many
	 * slices we should use, cap it automatically to the
	 * number of CPUs currently online */
	if (myri10ge_max_slices == -1)
		myri10ge_max_slices = ncpus;

	if (mgp->num_slices > myri10ge_max_slices)
		mgp->num_slices = myri10ge_max_slices;

	/* Now try to allocate as many MSI-X vectors as we have
	 * slices. We give up on MSI-X if we can only get a single
	 * vector. */

	mgp->msix_vectors = kzalloc(mgp->num_slices *
				    sizeof(*mgp->msix_vectors), GFP_KERNEL);
	if (mgp->msix_vectors == NULL)
		goto disable_msix;
	for (i = 0; i < mgp->num_slices; i++) {
		mgp->msix_vectors[i].entry = i;
	}

	while (mgp->num_slices > 1) {
		/* make sure it is a power of two */
		while (!is_power_of_2(mgp->num_slices))
			mgp->num_slices--;
		if (mgp->num_slices == 1)
			goto disable_msix;
		status = pci_enable_msix(pdev, mgp->msix_vectors,
					 mgp->num_slices);
		if (status == 0) {
			pci_disable_msix(pdev);
			return;
		}
		if (status > 0)
			mgp->num_slices = status;
		else
			goto disable_msix;
	}

disable_msix:
	if (mgp->msix_vectors != NULL) {
		kfree(mgp->msix_vectors);
		mgp->msix_vectors = NULL;
	}

abort_with_fw:
	mgp->num_slices = 1;
	mgp->fw_name = old_fw;
	myri10ge_load_firmware(mgp, 0);
}