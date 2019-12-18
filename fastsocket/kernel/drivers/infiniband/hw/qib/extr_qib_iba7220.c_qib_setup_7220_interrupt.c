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
struct qib_devdata {TYPE_1__* cspec; scalar_t__ msi_lo; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  QIB_DRV_NAME ; 
 int /*<<< orphan*/  qib_7220intr ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qib_devdata*) ; 

__attribute__((used)) static void qib_setup_7220_interrupt(struct qib_devdata *dd)
{
	if (!dd->cspec->irq)
		qib_dev_err(dd,
			"irq is 0, BIOS error?  Interrupts won't work\n");
	else {
		int ret = request_irq(dd->cspec->irq, qib_7220intr,
			dd->msi_lo ? 0 : IRQF_SHARED,
			QIB_DRV_NAME, dd);

		if (ret)
			qib_dev_err(dd,
				"Couldn't setup %s interrupt (irq=%d): %d\n",
				dd->msi_lo ?  "MSI" : "INTx",
				dd->cspec->irq, ret);
	}
}