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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int dummy; } ;
struct iwl_trans_pcie {int /*<<< orphan*/  drv; } ;
struct iwl_trans {int /*<<< orphan*/  dbgfs_dir; } ;
struct iwl_cfg {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_drv_start (struct iwl_trans*,struct iwl_cfg const*) ; 
 int /*<<< orphan*/  iwl_drv_stop (int /*<<< orphan*/ ) ; 
 int iwl_trans_dbgfs_register (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 struct iwl_trans* iwl_trans_pcie_alloc (struct pci_dev*,struct pci_device_id const*,struct iwl_cfg const*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_free (struct iwl_trans*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct iwl_trans*) ; 

__attribute__((used)) static int iwl_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	const struct iwl_cfg *cfg = (struct iwl_cfg *)(ent->driver_data);
	struct iwl_trans *iwl_trans;
	struct iwl_trans_pcie *trans_pcie;
	int ret;

	iwl_trans = iwl_trans_pcie_alloc(pdev, ent, cfg);
	if (iwl_trans == NULL)
		return -ENOMEM;

	pci_set_drvdata(pdev, iwl_trans);

	trans_pcie = IWL_TRANS_GET_PCIE_TRANS(iwl_trans);
	trans_pcie->drv = iwl_drv_start(iwl_trans, cfg);

	if (IS_ERR_OR_NULL(trans_pcie->drv)) {
		ret = PTR_ERR(trans_pcie->drv);
		goto out_free_trans;
	}

	/* register transport layer debugfs here */
	ret = iwl_trans_dbgfs_register(iwl_trans, iwl_trans->dbgfs_dir);
	if (ret)
		goto out_free_drv;

	return 0;

out_free_drv:
	iwl_drv_stop(trans_pcie->drv);
out_free_trans:
	iwl_trans_pcie_free(iwl_trans);
	pci_set_drvdata(pdev, NULL);
	return ret;
}