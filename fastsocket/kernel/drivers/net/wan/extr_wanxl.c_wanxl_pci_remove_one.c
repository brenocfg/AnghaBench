#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_11__ {int n_ports; int /*<<< orphan*/  status_address; TYPE_6__* status; scalar_t__ plx; scalar_t__* rx_skbs; int /*<<< orphan*/  pdev; scalar_t__ irq; TYPE_1__* ports; } ;
typedef  TYPE_3__ card_t ;
typedef  int /*<<< orphan*/  card_status_t ;
struct TYPE_12__ {TYPE_2__* rx_descs; } ;
struct TYPE_10__ {int /*<<< orphan*/  address; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_QUEUE_LENGTH ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_hdlc_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wanxl_reset (TYPE_3__*) ; 

__attribute__((used)) static void wanxl_pci_remove_one(struct pci_dev *pdev)
{
	card_t *card = pci_get_drvdata(pdev);
	int i;

	for (i = 0; i < card->n_ports; i++) {
		unregister_hdlc_device(card->ports[i].dev);
		free_netdev(card->ports[i].dev);
	}

	/* unregister and free all host resources */
	if (card->irq)
		free_irq(card->irq, card);

	wanxl_reset(card);

	for (i = 0; i < RX_QUEUE_LENGTH; i++)
		if (card->rx_skbs[i]) {
			pci_unmap_single(card->pdev,
					 card->status->rx_descs[i].address,
					 BUFFER_LENGTH, PCI_DMA_FROMDEVICE);
			dev_kfree_skb(card->rx_skbs[i]);
		}

	if (card->plx)
		iounmap(card->plx);

	if (card->status)
		pci_free_consistent(pdev, sizeof(card_status_t),
				    card->status, card->status_address);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	kfree(card);
}