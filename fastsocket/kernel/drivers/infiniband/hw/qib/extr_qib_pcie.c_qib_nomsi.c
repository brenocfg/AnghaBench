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
struct qib_devdata {int /*<<< orphan*/  pcidev; scalar_t__ msi_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 

void qib_nomsi(struct qib_devdata *dd)
{
	dd->msi_lo = 0;
	pci_disable_msi(dd->pcidev);
}