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
struct pci_dev {int devfn; TYPE_2__* bus; } ;
struct bnx2x_sriov {int offset; int stride; } ;
struct bnx2x {TYPE_1__* vfdb; struct pci_dev* pdev; } ;
struct TYPE_4__ {int number; } ;
struct TYPE_3__ {struct bnx2x_sriov sriov; } ;

/* Variables and functions */

__attribute__((used)) static int bnx2x_vf_bus(struct bnx2x *bp, int vfid)
{
	struct pci_dev *dev = bp->pdev;
	struct bnx2x_sriov *iov = &bp->vfdb->sriov;

	return dev->bus->number + ((dev->devfn + iov->offset +
				    iov->stride * vfid) >> 8);
}