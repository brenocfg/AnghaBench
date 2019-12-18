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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct bnx2x_virtf {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int bnx2x_is_pcie_pending (struct pci_dev*) ; 
 struct bnx2x_virtf* bnx2x_vf_by_abs_fid (struct bnx2x*,int) ; 
 struct pci_dev* pci_get_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 bnx2x_vf_is_pcie_pending(struct bnx2x *bp, u8 abs_vfid)
{
	struct pci_dev *dev;
	struct bnx2x_virtf *vf = bnx2x_vf_by_abs_fid(bp, abs_vfid);

	if (!vf)
		return false;

	dev = pci_get_bus_and_slot(vf->bus, vf->devfn);
	if (dev)
		return bnx2x_is_pcie_pending(dev);
	return false;
}