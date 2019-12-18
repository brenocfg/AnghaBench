#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct whci_dev {int dummy; } ;
struct whci_card {int n_caps; int /*<<< orphan*/  uwbbase; struct pci_dev* pci; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UWBCAPDATA_SIZE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct whci_card*) ; 
 struct whci_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct whci_card*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int whci_add_cap (struct whci_card*,int) ; 
 int whci_n_caps (struct pci_dev*) ; 

__attribute__((used)) static int whci_probe(struct pci_dev *pci, const struct pci_device_id *id)
{
	struct whci_card *card;
	int err, n_caps, n;

	err = pci_enable_device(pci);
	if (err < 0)
		goto error;
	pci_enable_msi(pci);
	pci_set_master(pci);
	err = -ENXIO;
	if (!pci_set_dma_mask(pci, DMA_BIT_MASK(64)))
		pci_set_consistent_dma_mask(pci, DMA_BIT_MASK(64));
	else if (!pci_set_dma_mask(pci, DMA_BIT_MASK(32)))
		pci_set_consistent_dma_mask(pci, DMA_BIT_MASK(32));
	else
		goto error_dma;

	err = n_caps = whci_n_caps(pci);
	if (n_caps < 0)
		goto error_ncaps;

	err = -ENOMEM;
	card = kzalloc(sizeof(struct whci_card)
		       + sizeof(struct whci_dev *) * (n_caps + 1),
		       GFP_KERNEL);
	if (card == NULL)
		goto error_kzalloc;
	card->pci = pci;
	card->n_caps = n_caps;

	err = -EBUSY;
	if (!request_mem_region(pci_resource_start(pci, 0),
				UWBCAPDATA_SIZE(card->n_caps),
				"whci (capability data)"))
		goto error_request_memregion;
	err = -ENOMEM;
	card->uwbbase = pci_iomap(pci, 0, UWBCAPDATA_SIZE(card->n_caps));
	if (!card->uwbbase)
		goto error_iomap;

	/* Add each capability. */
	for (n = 0; n <= card->n_caps; n++) {
		err = whci_add_cap(card, n);
		if (err < 0 && n == 0) {
			dev_err(&pci->dev, "cannot bind UWB radio controller:"
				" %d\n", err);
			goto error_bind;
		}
		if (err < 0)
			dev_warn(&pci->dev, "warning: cannot bind capability "
				 "#%u: %d\n", n, err);
	}
	pci_set_drvdata(pci, card);
	return 0;

error_bind:
	pci_iounmap(pci, card->uwbbase);
error_iomap:
	release_mem_region(pci_resource_start(pci, 0), UWBCAPDATA_SIZE(card->n_caps));
error_request_memregion:
	kfree(card);
error_kzalloc:
error_ncaps:
error_dma:
	pci_disable_msi(pci);
	pci_disable_device(pci);
error:
	return err;
}