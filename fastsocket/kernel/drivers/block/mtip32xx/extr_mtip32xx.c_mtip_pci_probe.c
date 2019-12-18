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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct driver_data {int /*<<< orphan*/  online_list; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/  remove_list; struct pci_dev* pdev; int /*<<< orphan*/  instance; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MTIP_ABAR ; 
 int /*<<< orphan*/  MTIP_DDF_INIT_DONE_BIT ; 
 int /*<<< orphan*/  MTIP_DRV_NAME ; 
 int MTIP_FTL_REBUILD_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_lock ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  instance ; 
 int /*<<< orphan*/  kfree (struct driver_data*) ; 
 struct driver_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtip_block_initialize (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_major ; 
 int /*<<< orphan*/  online_list ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct driver_data*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcim_iounmap_regions (struct pci_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mtip_pci_probe(struct pci_dev *pdev,
			const struct pci_device_id *ent)
{
	int rv = 0;
	struct driver_data *dd = NULL;
	unsigned long flags;

	/* Allocate memory for this devices private data. */
	dd = kzalloc(sizeof(struct driver_data), GFP_KERNEL);
	if (dd == NULL) {
		dev_err(&pdev->dev,
			"Unable to allocate memory for driver data\n");
		return -ENOMEM;
	}

	/* Attach the private data to this PCI device.  */
	pci_set_drvdata(pdev, dd);

	rv = pcim_enable_device(pdev);
	if (rv < 0) {
		dev_err(&pdev->dev, "Unable to enable device\n");
		goto iomap_err;
	}

	/* Map BAR5 to memory. */
	rv = pcim_iomap_regions(pdev, 1 << MTIP_ABAR, MTIP_DRV_NAME);
	if (rv < 0) {
		dev_err(&pdev->dev, "Unable to map regions\n");
		goto iomap_err;
	}

	if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
		rv = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));

		if (rv) {
			rv = pci_set_consistent_dma_mask(pdev,
						DMA_BIT_MASK(32));
			if (rv) {
				dev_warn(&pdev->dev,
					"64-bit DMA enable failed\n");
				goto setmask_err;
			}
		}
	}

	pci_set_master(pdev);
	rv = pci_enable_msi(pdev);
	if (rv) {
		dev_warn(&pdev->dev,
			"Unable to enable MSI interrupt.\n");
		goto block_initialize_err;
	}

	/* Copy the info we may need later into the private data structure. */
	dd->major	= mtip_major;
	dd->instance	= instance;
	dd->pdev	= pdev;

	INIT_LIST_HEAD(&dd->online_list);
	INIT_LIST_HEAD(&dd->remove_list);

	/* Initialize the block layer. */
	rv = mtip_block_initialize(dd);
	if (rv < 0) {
		dev_err(&pdev->dev,
			"Unable to initialize block layer\n");
		goto block_initialize_err;
	}

	/*
	 * Increment the instance count so that each device has a unique
	 * instance number.
	 */
	instance++;
	if (rv != MTIP_FTL_REBUILD_MAGIC)
		set_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag);
	else
		rv = 0; /* device in rebuild state, return 0 from probe */

	/* Add to online list even if in ftl rebuild */
	spin_lock_irqsave(&dev_lock, flags);
	list_add(&dd->online_list, &online_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	goto done;

block_initialize_err:
	pci_disable_msi(pdev);

setmask_err:
	pcim_iounmap_regions(pdev, 1 << MTIP_ABAR);

iomap_err:
	kfree(dd);
	pci_set_drvdata(pdev, NULL);
	return rv;
done:
	return rv;
}