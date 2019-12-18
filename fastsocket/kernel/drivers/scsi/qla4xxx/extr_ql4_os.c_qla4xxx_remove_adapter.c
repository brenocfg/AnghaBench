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
struct scsi_qla_host {int /*<<< orphan*/  host; scalar_t__ boot_kset; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct scsi_qla_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql4xdisablesysfsboot ; 
 int /*<<< orphan*/  qla4_8xxx_free_sysfs_attr (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_destroy_fw_ddb_session (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_destroy_ifaces (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_free_adapter (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_prevent_other_port_reinit (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_sysfs_ddb_remove (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4xxx_remove_adapter(struct pci_dev *pdev)
{
	struct scsi_qla_host *ha;

	/*
	 * If the PCI device is disabled then it means probe_adapter had
	 * failed and resources already cleaned up on probe_adapter exit.
	 */
	if (!pci_is_enabled(pdev))
		return;

	ha = pci_get_drvdata(pdev);

	if (is_qla40XX(ha))
		qla4xxx_prevent_other_port_reinit(ha);

	/* destroy iface from sysfs */
	qla4xxx_destroy_ifaces(ha);

	if ((!ql4xdisablesysfsboot) && ha->boot_kset)
		iscsi_boot_destroy_kset(ha->boot_kset);

	qla4xxx_destroy_fw_ddb_session(ha);
	qla4_8xxx_free_sysfs_attr(ha);

	qla4xxx_sysfs_ddb_remove(ha);
	scsi_remove_host(ha->host);

	qla4xxx_free_adapter(ha);

	scsi_host_put(ha->host);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}