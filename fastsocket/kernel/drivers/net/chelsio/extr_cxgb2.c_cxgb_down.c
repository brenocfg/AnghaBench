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
struct TYPE_3__ {scalar_t__ has_msi; } ;
struct adapter {TYPE_2__* pdev; TYPE_1__ params; int /*<<< orphan*/  sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adapter*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 int /*<<< orphan*/  t1_interrupts_disable (struct adapter*) ; 
 int /*<<< orphan*/  t1_sge_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxgb_down(struct adapter *adapter)
{
	t1_sge_stop(adapter->sge);
	t1_interrupts_disable(adapter);
	free_irq(adapter->pdev->irq, adapter);
	if (adapter->params.has_msi)
		pci_disable_msi(adapter->pdev);
}