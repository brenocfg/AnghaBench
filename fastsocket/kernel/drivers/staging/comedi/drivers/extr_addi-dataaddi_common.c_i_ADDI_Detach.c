#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ irq; scalar_t__ private; } ;
struct TYPE_6__ {int /*<<< orphan*/  amcc; scalar_t__ allocated; scalar_t__ dw_AiBase; int /*<<< orphan*/ * ui_DmaBufferPages; scalar_t__* ul_DmaBufferVirtual; TYPE_1__* ps_BoardInfo; scalar_t__ b_ValidDriver; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_VendorId; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pc_EepromChip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDIDATA_9054 ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_ADDI_Reset (struct comedi_device*) ; 
 int /*<<< orphan*/  i_pci_card_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 scalar_t__ pci_list_builded ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* this_board ; 
 int /*<<< orphan*/  v_pci_card_list_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i_ADDI_Detach(struct comedi_device *dev)
{

	if (dev->private) {
		if (devpriv->b_ValidDriver) {
			i_ADDI_Reset(dev);
		}

		if (dev->irq) {
			free_irq(dev->irq, dev);
		}

		if ((devpriv->ps_BoardInfo->pc_EepromChip == NULL)
			|| (strcmp(devpriv->ps_BoardInfo->pc_EepromChip,
					ADDIDATA_9054) != 0)) {
			if (devpriv->allocated) {
				i_pci_card_free(devpriv->amcc);
			}

			if (devpriv->ul_DmaBufferVirtual[0]) {
				free_pages((unsigned long)devpriv->
					ul_DmaBufferVirtual[0],
					devpriv->ui_DmaBufferPages[0]);
			}

			if (devpriv->ul_DmaBufferVirtual[1]) {
				free_pages((unsigned long)devpriv->
					ul_DmaBufferVirtual[1],
					devpriv->ui_DmaBufferPages[1]);
			}
		} else {
			iounmap((void *)devpriv->dw_AiBase);

			if (devpriv->allocated) {
				i_pci_card_free(devpriv->amcc);
			}
		}

		if (pci_list_builded) {
			/* v_pci_card_list_cleanup(PCI_VENDOR_ID_AMCC); */
			v_pci_card_list_cleanup(this_board->i_VendorId);
			pci_list_builded = 0;
		}
	}

	return 0;
}