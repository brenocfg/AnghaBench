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
struct saa7146_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_present; struct saa7146_dev* dev; } ;
struct budget_ci {int slot_status; int /*<<< orphan*/  ca; TYPE_1__ budget; } ;

/* Variables and functions */
 unsigned int CICONTROL_CAMDETECT ; 
 int /*<<< orphan*/  DEBIADDR_CICONTROL ; 
 int /*<<< orphan*/  DEBICICTL ; 
 int /*<<< orphan*/  DVB_CA_EN50221_CAMCHANGE_INSERTED ; 
 int /*<<< orphan*/  DVB_CA_EN50221_CAMCHANGE_REMOVED ; 
 int /*<<< orphan*/  SAA7146_GPIO_IRQHI ; 
 int /*<<< orphan*/  SAA7146_GPIO_IRQLO ; 
 int SLOTSTATUS_NONE ; 
 int SLOTSTATUS_OCCUPIED ; 
 int SLOTSTATUS_PRESENT ; 
 int SLOTSTATUS_READY ; 
 int SLOTSTATUS_RESET ; 
 int /*<<< orphan*/  dvb_ca_en50221_camchange_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_ca_en50221_camready_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_ca_en50221_frda_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ttpci_budget_debiread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ciintf_interrupt(unsigned long data)
{
	struct budget_ci *budget_ci = (struct budget_ci *) data;
	struct saa7146_dev *saa = budget_ci->budget.dev;
	unsigned int flags;

	// ensure we don't get spurious IRQs during initialisation
	if (!budget_ci->budget.ci_present)
		return;

	// read the CAM status
	flags = ttpci_budget_debiread(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	if (flags & CICONTROL_CAMDETECT) {

		// GPIO should be set to trigger on falling edge if a CAM is present
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQLO);

		if (budget_ci->slot_status & SLOTSTATUS_NONE) {
			// CAM insertion IRQ
			budget_ci->slot_status = SLOTSTATUS_PRESENT;
			dvb_ca_en50221_camchange_irq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_INSERTED);

		} else if (budget_ci->slot_status & SLOTSTATUS_RESET) {
			// CAM ready (reset completed)
			budget_ci->slot_status = SLOTSTATUS_READY;
			dvb_ca_en50221_camready_irq(&budget_ci->ca, 0);

		} else if (budget_ci->slot_status & SLOTSTATUS_READY) {
			// FR/DA IRQ
			dvb_ca_en50221_frda_irq(&budget_ci->ca, 0);
		}
	} else {

		// trigger on rising edge if a CAM is not present - when a CAM is inserted, we
		// only want to get the IRQ when it sets READY. If we trigger on the falling edge,
		// the CAM might not actually be ready yet.
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IRQHI);

		// generate a CAM removal IRQ if we haven't already
		if (budget_ci->slot_status & SLOTSTATUS_OCCUPIED) {
			// CAM removal IRQ
			budget_ci->slot_status = SLOTSTATUS_NONE;
			dvb_ca_en50221_camchange_irq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_REMOVED);
		}
	}
}