#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct pci_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  capi_ctrl; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_8__ {size_t nr_controllers; int /*<<< orphan*/  dma; int /*<<< orphan*/  port; int /*<<< orphan*/  mbase; int /*<<< orphan*/  irq; TYPE_1__* ctrlinfo; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  AVMB1_PORTLEN ; 
 int /*<<< orphan*/  avmcard_dma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_free_card (TYPE_2__*) ; 
 int /*<<< orphan*/  c4_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  detach_capi_ctr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_2__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c4_remove(struct pci_dev *pdev)
{
	avmcard *card = pci_get_drvdata(pdev);
	avmctrl_info *cinfo;
	u_int i;

	if (!card)
		return;

 	c4_reset(card);

        for (i=0; i < card->nr_controllers; i++) {
		cinfo = &card->ctrlinfo[i];
		detach_capi_ctr(&cinfo->capi_ctrl);
	}

	free_irq(card->irq, card);
	iounmap(card->mbase);
	release_region(card->port, AVMB1_PORTLEN);
        avmcard_dma_free(card->dma);
        pci_set_drvdata(pdev, NULL);
	b1_free_card(card);
}