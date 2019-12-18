#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qib_devdata {TYPE_2__* pcidev; TYPE_1__* cspec; int /*<<< orphan*/  msi_lo; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_7220_free_irq (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_devinfo (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  qib_enable_intx (TYPE_2__*) ; 
 int /*<<< orphan*/  qib_setup_7220_interrupt (struct qib_devdata*) ; 

__attribute__((used)) static int qib_7220_intr_fallback(struct qib_devdata *dd)
{
	if (!dd->msi_lo)
		return 0;

	qib_devinfo(dd->pcidev,
		"MSI interrupt not detected, trying INTx interrupts\n");
	qib_7220_free_irq(dd);
	qib_enable_intx(dd->pcidev);
	/*
	 * Some newer kernels require free_irq before disable_msi,
	 * and irq can be changed during disable and INTx enable
	 * and we need to therefore use the pcidev->irq value,
	 * not our saved MSI value.
	 */
	dd->cspec->irq = dd->pcidev->irq;
	qib_setup_7220_interrupt(dd);
	return 1;
}