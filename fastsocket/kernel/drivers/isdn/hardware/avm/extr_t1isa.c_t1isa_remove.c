#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  capi_ctrl; TYPE_2__* card; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  irq; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  AVMB1_PORTLEN ; 
 int /*<<< orphan*/  b1_free_card (TYPE_2__*) ; 
 int /*<<< orphan*/  b1_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_capi_ctr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t1isa_remove(struct pci_dev *pdev)
{
	avmctrl_info *cinfo = pci_get_drvdata(pdev);
	avmcard *card;
	
	if (!cinfo)
		return;

	card = cinfo->card;

	t1_disable_irq(card->port);
	b1_reset(card->port);
	b1_reset(card->port);
	t1_reset(card->port);

	detach_capi_ctr(&cinfo->capi_ctrl);
	free_irq(card->irq, card);
	release_region(card->port, AVMB1_PORTLEN);
	b1_free_card(card);
}