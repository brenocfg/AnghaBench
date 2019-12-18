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
struct r592_device {int /*<<< orphan*/  mmio; int /*<<< orphan*/  io_thread; int /*<<< orphan*/  dummy_dma_page_physical_address; scalar_t__ dummy_dma_page; int /*<<< orphan*/  irq; int /*<<< orphan*/  detect_timer; int /*<<< orphan*/  pio_fifo; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  io_thread_lock; int /*<<< orphan*/  irq_lock; struct pci_dev* pci_dev; struct memstick_host* host; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct memstick_host {int /*<<< orphan*/  set_param; int /*<<< orphan*/  request; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMSTICK_CAP_PAR4 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct r592_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct r592_device*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ memstick_add_host (struct memstick_host*) ; 
 struct memstick_host* memstick_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memstick_free_host (struct memstick_host*) ; 
 struct r592_device* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  message (char*) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct r592_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  r592_check_dma (struct r592_device*) ; 
 int /*<<< orphan*/  r592_detect_timer ; 
 int /*<<< orphan*/  r592_irq ; 
 int /*<<< orphan*/  r592_process_thread ; 
 int /*<<< orphan*/  r592_set_param ; 
 int /*<<< orphan*/  r592_stop_dma (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_submit_req ; 
 int /*<<< orphan*/  r592_update_card_detect (struct r592_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct r592_device*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r592_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int error = -ENOMEM;
	struct memstick_host *host;
	struct r592_device *dev;

	/* Allocate memory */
	host = memstick_alloc_host(sizeof(struct r592_device), &pdev->dev);
	if (!host)
		goto error1;

	dev = memstick_priv(host);
	dev->host = host;
	dev->pci_dev = pdev;
	pci_set_drvdata(pdev, dev);

	/* pci initialization */
	error = pci_enable_device(pdev);
	if (error)
		goto error2;

	pci_set_master(pdev);
	error = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (error)
		goto error3;

	error = pci_request_regions(pdev, DRV_NAME);
	if (error)
		goto error3;

	dev->mmio = pci_ioremap_bar(pdev, 0);
	if (!dev->mmio)
		goto error4;

	dev->irq = pdev->irq;
	spin_lock_init(&dev->irq_lock);
	spin_lock_init(&dev->io_thread_lock);
	init_completion(&dev->dma_done);
	INIT_KFIFO(dev->pio_fifo);
	setup_timer(&dev->detect_timer,
		r592_detect_timer, (long unsigned int)dev);

	/* Host initialization */
	host->caps = MEMSTICK_CAP_PAR4;
	host->request = r592_submit_req;
	host->set_param = r592_set_param;
	r592_check_dma(dev);

	dev->io_thread = kthread_run(r592_process_thread, dev, "r592_io");
	if (IS_ERR(dev->io_thread)) {
		error = PTR_ERR(dev->io_thread);
		goto error5;
	}

	/* This is just a precation, so don't fail */
	dev->dummy_dma_page = pci_alloc_consistent(pdev, PAGE_SIZE,
		&dev->dummy_dma_page_physical_address);
	r592_stop_dma(dev , 0);

	if (request_irq(dev->irq, &r592_irq, IRQF_SHARED,
			  DRV_NAME, dev))
		goto error6;

	r592_update_card_detect(dev);
	if (memstick_add_host(host))
		goto error7;

	message("driver succesfully loaded");
	return 0;
error7:
	free_irq(dev->irq, dev);
error6:
	if (dev->dummy_dma_page)
		pci_free_consistent(pdev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physical_address);

	kthread_stop(dev->io_thread);
error5:
	iounmap(dev->mmio);
error4:
	pci_release_regions(pdev);
error3:
	pci_disable_device(pdev);
error2:
	memstick_free_host(host);
error1:
	return error;
}