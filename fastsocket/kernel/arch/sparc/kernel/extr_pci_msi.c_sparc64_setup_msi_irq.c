#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sparc64_msiq_ops {int (* msi_setup ) (struct pci_pbm_info*,int /*<<< orphan*/ ,int,int) ;} ;
struct pci_pbm_info {unsigned int* msi_irq_table; int msi_first; int msi64_start; int msi32_start; struct sparc64_msiq_ops* msi_ops; } ;
struct TYPE_4__ {struct pci_pbm_info* host_controller; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct msi_msg {int address_hi; int address_lo; int data; } ;
struct TYPE_6__ {scalar_t__ is_64; } ;
struct msi_desc {TYPE_3__ msi_attrib; } ;

/* Variables and functions */
 int ENOMEM ; 
 int alloc_msi (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  free_msi (struct pci_pbm_info*,int) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  msi_irq ; 
 int /*<<< orphan*/  pick_msiq (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_irq_msi (unsigned int,struct msi_desc*) ; 
 int stub1 (struct pci_pbm_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int virt_irq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_irq_free (unsigned int) ; 
 int /*<<< orphan*/  write_msi_msg (unsigned int,struct msi_msg*) ; 

__attribute__((used)) static int sparc64_setup_msi_irq(unsigned int *virt_irq_p,
				 struct pci_dev *pdev,
				 struct msi_desc *entry)
{
	struct pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	const struct sparc64_msiq_ops *ops = pbm->msi_ops;
	struct msi_msg msg;
	int msi, err;
	u32 msiqid;

	*virt_irq_p = virt_irq_alloc(0, 0);
	err = -ENOMEM;
	if (!*virt_irq_p)
		goto out_err;

	set_irq_chip_and_handler_name(*virt_irq_p, &msi_irq,
				      handle_simple_irq, "MSI");

	err = alloc_msi(pbm);
	if (unlikely(err < 0))
		goto out_virt_irq_free;

	msi = err;

	msiqid = pick_msiq(pbm);

	err = ops->msi_setup(pbm, msiqid, msi,
			     (entry->msi_attrib.is_64 ? 1 : 0));
	if (err)
		goto out_msi_free;

	pbm->msi_irq_table[msi - pbm->msi_first] = *virt_irq_p;

	if (entry->msi_attrib.is_64) {
		msg.address_hi = pbm->msi64_start >> 32;
		msg.address_lo = pbm->msi64_start & 0xffffffff;
	} else {
		msg.address_hi = 0;
		msg.address_lo = pbm->msi32_start;
	}
	msg.data = msi;

	set_irq_msi(*virt_irq_p, entry);
	write_msi_msg(*virt_irq_p, &msg);

	return 0;

out_msi_free:
	free_msi(pbm, msi);

out_virt_irq_free:
	set_irq_chip(*virt_irq_p, NULL);
	virt_irq_free(*virt_irq_p);
	*virt_irq_p = 0;

out_err:
	return err;
}