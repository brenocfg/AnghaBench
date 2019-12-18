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
struct sparc64_msiq_ops {int dummy; } ;
struct pci_pbm_info {int msiq_num; int msiq_first; int msiq_first_devino; } ;

/* Variables and functions */
 int bringup_one_msi_queue (struct pci_pbm_info*,struct sparc64_msiq_ops const*,unsigned long,unsigned long) ; 

__attribute__((used)) static int sparc64_bringup_msi_queues(struct pci_pbm_info *pbm,
				      const struct sparc64_msiq_ops *ops)
{
	int i;

	for (i = 0; i < pbm->msiq_num; i++) {
		unsigned long msiqid = i + pbm->msiq_first;
		unsigned long devino = i + pbm->msiq_first_devino;
		int err;

		err = bringup_one_msi_queue(pbm, ops, msiqid, devino);
		if (err)
			return err;
	}

	return 0;
}