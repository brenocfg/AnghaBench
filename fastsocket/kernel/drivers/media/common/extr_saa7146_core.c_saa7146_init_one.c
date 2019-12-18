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
struct saa7146_pci_extension_data {struct saa7146_extension* ext; } ;
struct saa7146_extension {scalar_t__ (* attach ) (struct saa7146_dev*,struct saa7146_pci_extension_data*) ;scalar_t__ (* probe ) (struct saa7146_dev*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dma_handle; void* cpu_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_handle; void* cpu_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_handle; void* cpu_addr; } ;
struct saa7146_dev {int revision; int /*<<< orphan*/  mem; TYPE_3__ d_rps0; TYPE_2__ d_rps1; TYPE_1__ d_i2c; int /*<<< orphan*/  item; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  i2c_wq; int /*<<< orphan*/  module; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  int_slock; int /*<<< orphan*/  v4l2_lock; struct saa7146_extension* ext; int /*<<< orphan*/  name; struct pci_dev* pci; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  INFO (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  PCI_BT_V1 ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  SAA7146_RPS_MEM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interrupt_hw ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct saa7146_dev*) ; 
 struct saa7146_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* pci_alloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct saa7146_dev*) ; 
 int /*<<< orphan*/  saa7146_devices ; 
 int saa7146_num ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub1 (struct saa7146_dev*) ; 
 scalar_t__ stub2 (struct saa7146_dev*,struct saa7146_pci_extension_data*) ; 

__attribute__((used)) static int saa7146_init_one(struct pci_dev *pci, const struct pci_device_id *ent)
{
	struct saa7146_pci_extension_data *pci_ext = (struct saa7146_pci_extension_data *)ent->driver_data;
	struct saa7146_extension *ext = pci_ext->ext;
	struct saa7146_dev *dev;
	int err = -ENOMEM;

	/* clear out mem for sure */
	dev = kzalloc(sizeof(struct saa7146_dev), GFP_KERNEL);
	if (!dev) {
		ERR(("out of memory.\n"));
		goto out;
	}

	DEB_EE(("pci:%p\n",pci));

	err = pci_enable_device(pci);
	if (err < 0) {
		ERR(("pci_enable_device() failed.\n"));
		goto err_free;
	}

	/* enable bus-mastering */
	pci_set_master(pci);

	dev->pci = pci;

	/* get chip-revision; this is needed to enable bug-fixes */
	err = pci_read_config_dword(pci, PCI_CLASS_REVISION, &dev->revision);
	if (err < 0) {
		ERR(("pci_read_config_dword() failed.\n"));
		goto err_disable;
	}
	dev->revision &= 0xf;

	/* remap the memory from virtual to physical address */

	err = pci_request_region(pci, 0, "saa7146");
	if (err < 0)
		goto err_disable;

	dev->mem = ioremap(pci_resource_start(pci, 0),
			   pci_resource_len(pci, 0));
	if (!dev->mem) {
		ERR(("ioremap() failed.\n"));
		err = -ENODEV;
		goto err_release;
	}

	/* we don't do a master reset here anymore, it screws up
	   some boards that don't have an i2c-eeprom for configuration
	   values */
/*
	saa7146_write(dev, MC1, MASK_31);
*/

	/* disable all irqs */
	saa7146_write(dev, IER, 0);

	/* shut down all dma transfers and rps tasks */
	saa7146_write(dev, MC1, 0x30ff0000);

	/* clear out any rps-signals pending */
	saa7146_write(dev, MC2, 0xf8000000);

	/* request an interrupt for the saa7146 */
	err = request_irq(pci->irq, interrupt_hw, IRQF_SHARED | IRQF_DISABLED,
			  dev->name, dev);
	if (err < 0) {
		ERR(("request_irq() failed.\n"));
		goto err_unmap;
	}

	err = -ENOMEM;

	/* get memory for various stuff */
	dev->d_rps0.cpu_addr = pci_alloc_consistent(pci, SAA7146_RPS_MEM,
						    &dev->d_rps0.dma_handle);
	if (!dev->d_rps0.cpu_addr)
		goto err_free_irq;
	memset(dev->d_rps0.cpu_addr, 0x0, SAA7146_RPS_MEM);

	dev->d_rps1.cpu_addr = pci_alloc_consistent(pci, SAA7146_RPS_MEM,
						    &dev->d_rps1.dma_handle);
	if (!dev->d_rps1.cpu_addr)
		goto err_free_rps0;
	memset(dev->d_rps1.cpu_addr, 0x0, SAA7146_RPS_MEM);

	dev->d_i2c.cpu_addr = pci_alloc_consistent(pci, SAA7146_RPS_MEM,
						   &dev->d_i2c.dma_handle);
	if (!dev->d_i2c.cpu_addr)
		goto err_free_rps1;
	memset(dev->d_i2c.cpu_addr, 0x0, SAA7146_RPS_MEM);

	/* the rest + print status message */

	/* create a nice device name */
	sprintf(dev->name, "saa7146 (%d)", saa7146_num);

	INFO(("found saa7146 @ mem %p (revision %d, irq %d) (0x%04x,0x%04x).\n", dev->mem, dev->revision, pci->irq, pci->subsystem_vendor, pci->subsystem_device));
	dev->ext = ext;

	mutex_init(&dev->v4l2_lock);
	spin_lock_init(&dev->int_slock);
	spin_lock_init(&dev->slock);

	mutex_init(&dev->i2c_lock);

	dev->module = THIS_MODULE;
	init_waitqueue_head(&dev->i2c_wq);

	/* set some sane pci arbitrition values */
	saa7146_write(dev, PCI_BT_V1, 0x1c00101f);

	/* TODO: use the status code of the callback */

	err = -ENODEV;

	if (ext->probe && ext->probe(dev)) {
		DEB_D(("ext->probe() failed for %p. skipping device.\n",dev));
		goto err_free_i2c;
	}

	if (ext->attach(dev, pci_ext)) {
		DEB_D(("ext->attach() failed for %p. skipping device.\n",dev));
		goto err_free_i2c;
	}
	/* V4L extensions will set the pci drvdata to the v4l2_device in the
	   attach() above. So for those cards that do not use V4L we have to
	   set it explicitly. */
	pci_set_drvdata(pci, &dev->v4l2_dev);

	INIT_LIST_HEAD(&dev->item);
	list_add_tail(&dev->item,&saa7146_devices);
	saa7146_num++;

	err = 0;
out:
	return err;

err_free_i2c:
	pci_free_consistent(pci, SAA7146_RPS_MEM, dev->d_i2c.cpu_addr,
			    dev->d_i2c.dma_handle);
err_free_rps1:
	pci_free_consistent(pci, SAA7146_RPS_MEM, dev->d_rps1.cpu_addr,
			    dev->d_rps1.dma_handle);
err_free_rps0:
	pci_free_consistent(pci, SAA7146_RPS_MEM, dev->d_rps0.cpu_addr,
			    dev->d_rps0.dma_handle);
err_free_irq:
	free_irq(pci->irq, (void *)dev);
err_unmap:
	iounmap(dev->mem);
err_release:
	pci_release_region(pci, 0);
err_disable:
	pci_disable_device(pci);
err_free:
	kfree(dev);
	goto out;
}