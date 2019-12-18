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
struct qib_devdata {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_cleanup_aer_uncorrect_error_status (struct pci_dev*) ; 
 struct qib_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qib_devinfo (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  qib_init (struct qib_devdata*,int) ; 

__attribute__((used)) static void
qib_pci_resume(struct pci_dev *pdev)
{
	struct qib_devdata *dd = pci_get_drvdata(pdev);
	qib_devinfo(pdev, "QIB resume function called\n");
	pci_cleanup_aer_uncorrect_error_status(pdev);
	/*
	 * Running jobs will fail, since it's asynchronous
	 * unlike sysfs-requested reset.   Better than
	 * doing nothing.
	 */
	qib_init(dd, 1); /* same as re-init after reset */
}