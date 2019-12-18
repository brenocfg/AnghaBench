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
 int PCI_EXP_SLTCTL_ABPE ; 
 int PCI_EXP_SLTCTL_CCIE ; 
 int PCI_EXP_SLTCTL_HPIE ; 
 int PCI_EXP_SLTCTL_MRLSCE ; 
 int PCI_EXP_SLTCTL_PDCE ; 
 int PCI_EXP_SLTCTL_PFDE ; 
 int /*<<< orphan*/  ctrl_warn (struct controller*,char*) ; 
 scalar_t__ pcie_write_cmd (struct controller*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcie_disable_notification(struct controller *ctrl)
{
	u16 mask;
	mask = (PCI_EXP_SLTCTL_PDCE | PCI_EXP_SLTCTL_ABPE |
		PCI_EXP_SLTCTL_MRLSCE | PCI_EXP_SLTCTL_PFDE |
		PCI_EXP_SLTCTL_HPIE | PCI_EXP_SLTCTL_CCIE);
	if (pcie_write_cmd(ctrl, 0, mask))
		ctrl_warn(ctrl, "Cannot disable software notification\n");
}