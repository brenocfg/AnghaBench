#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qib_devdata {int /*<<< orphan*/  pcidev; TYPE_1__* cspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_msix_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_7322_nomsix (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qib_enable_intx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_setup_7322_interrupt (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_7322_intr_fallback(struct qib_devdata *dd)
{
	if (!dd->cspec->num_msix_entries)
		return 0; /* already using INTx */

	qib_devinfo(dd->pcidev,
		"MSIx interrupt not detected, trying INTx interrupts\n");
	qib_7322_nomsix(dd);
	qib_enable_intx(dd->pcidev);
	qib_setup_7322_interrupt(dd, 0);
	return 1;
}