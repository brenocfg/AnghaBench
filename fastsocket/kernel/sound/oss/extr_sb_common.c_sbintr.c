#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int irq_ok; int model; } ;
typedef  TYPE_1__ sb_devc ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  MDL_ESS 129 
#define  MDL_ESSPCI 128 
 int /*<<< orphan*/  ess_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  sb_intr (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t sbintr(int irq, void *dev_id)
{
	sb_devc *devc = dev_id;

	devc->irq_ok = 1;

	switch (devc->model) {
	case MDL_ESSPCI:
		pci_intr (devc);
		break;
		
	case MDL_ESS:
		ess_intr (devc);
		break;
	default:
		sb_intr (devc);
		break;
	}
	return IRQ_HANDLED;
}