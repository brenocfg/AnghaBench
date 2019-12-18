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
struct mite_struct {scalar_t__ used; scalar_t__ mite_phys_addr; int /*<<< orphan*/  pcidev; int /*<<< orphan*/ * daq_io_addr; int /*<<< orphan*/ * mite_io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

void mite_unsetup(struct mite_struct *mite)
{
	/* unsigned long offset, start, length; */

	if (!mite)
		return;

	if (mite->mite_io_addr) {
		iounmap(mite->mite_io_addr);
		mite->mite_io_addr = NULL;
	}
	if (mite->daq_io_addr) {
		iounmap(mite->daq_io_addr);
		mite->daq_io_addr = NULL;
	}
	if (mite->mite_phys_addr) {
		comedi_pci_disable(mite->pcidev);
		mite->mite_phys_addr = 0;
	}

	mite->used = 0;
}