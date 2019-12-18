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
typedef  int u16 ;
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATTN_BUTTN (struct controller*) ; 
 scalar_t__ MRL_SENS (struct controller*) ; 
 int PCI_EXP_SLTCTL_ABPE ; 
 int PCI_EXP_SLTCTL_CCIE ; 
 int PCI_EXP_SLTCTL_HPIE ; 
 int PCI_EXP_SLTCTL_MRLSCE ; 
 int PCI_EXP_SLTCTL_PDCE ; 
 int PCI_EXP_SLTCTL_PFDE ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 scalar_t__ pcie_write_cmd (struct controller*,int,int) ; 
 int /*<<< orphan*/  pciehp_poll_mode ; 

int pcie_enable_notification(struct controller *ctrl)
{
	u16 cmd, mask;

	cmd = PCI_EXP_SLTCTL_PDCE;
	if (ATTN_BUTTN(ctrl))
		cmd |= PCI_EXP_SLTCTL_ABPE;
	if (POWER_CTRL(ctrl))
		cmd |= PCI_EXP_SLTCTL_PFDE;
	if (MRL_SENS(ctrl))
		cmd |= PCI_EXP_SLTCTL_MRLSCE;
	if (!pciehp_poll_mode)
		cmd |= PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE;

	mask = (PCI_EXP_SLTCTL_PDCE | PCI_EXP_SLTCTL_ABPE |
		PCI_EXP_SLTCTL_MRLSCE | PCI_EXP_SLTCTL_PFDE |
		PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE);

	if (pcie_write_cmd(ctrl, cmd, mask)) {
		ctrl_err(ctrl, "Cannot enable software notification\n");
		return -1;
	}
	return 0;
}