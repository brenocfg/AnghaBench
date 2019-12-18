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
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/ * regs; } ;
struct resource {scalar_t__ start; scalar_t__ end; TYPE_1__* parent; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct hc_driver {int dummy; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int DMA_MEMORY_EXCLUSIVE ; 
 int DMA_MEMORY_MAP ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  SM501_GATE_USB_HOST ; 
 int /*<<< orphan*/  SM501_IRQ_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dma_declare_coherent_memory (struct device*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dma_release_declared_memory (struct device*) ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ohci_hcd_init (int /*<<< orphan*/ ) ; 
 struct hc_driver ohci_sm501_hc_driver ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_modify_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_unit_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_add_hcd (struct usb_hcd*,int,int) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_sm501_drv_probe(struct platform_device *pdev)
{
	const struct hc_driver *driver = &ohci_sm501_hc_driver;
	struct device *dev = &pdev->dev;
	struct resource	*res, *mem;
	int retval, irq;
	struct usb_hcd *hcd = NULL;

	irq = retval = platform_get_irq(pdev, 0);
	if (retval < 0)
		goto err0;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (mem == NULL) {
		dev_err(dev, "no resource definition for memory\n");
		retval = -ENOENT;
		goto err0;
	}

	if (!request_mem_region(mem->start, mem->end - mem->start + 1,
				pdev->name)) {
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err0;
	}

	/* The sm501 chip is equipped with local memory that may be used
	 * by on-chip devices such as the video controller and the usb host.
	 * This driver uses dma_declare_coherent_memory() to make sure
	 * usb allocations with dma_alloc_coherent() allocate from
	 * this local memory. The dma_handle returned by dma_alloc_coherent()
	 * will be an offset starting from 0 for the first local memory byte.
	 *
	 * So as long as data is allocated using dma_alloc_coherent() all is
	 * fine. This is however not always the case - buffers may be allocated
	 * using kmalloc() - so the usb core needs to be told that it must copy
	 * data into our local memory if the buffers happen to be placed in
	 * regular memory. The HCD_LOCAL_MEM flag does just that.
	 */

	if (!dma_declare_coherent_memory(dev, mem->start,
					 mem->start - mem->parent->start,
					 (mem->end - mem->start) + 1,
					 DMA_MEMORY_MAP |
					 DMA_MEMORY_EXCLUSIVE)) {
		dev_err(dev, "cannot declare coherent memory\n");
		retval = -ENXIO;
		goto err1;
	}

	/* allocate, reserve and remap resources for registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(dev, "no resource definition for registers\n");
		retval = -ENOENT;
		goto err2;
	}

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto err2;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = res->end - res->start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len,	pdev->name)) {
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err3;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (hcd->regs == NULL) {
		dev_err(dev, "cannot remap registers\n");
		retval = -ENXIO;
		goto err4;
	}

	ohci_hcd_init(hcd_to_ohci(hcd));

	retval = usb_add_hcd(hcd, irq, IRQF_DISABLED | IRQF_SHARED);
	if (retval)
		goto err4;

	/* enable power and unmask interrupts */

	sm501_unit_power(dev->parent, SM501_GATE_USB_HOST, 1);
	sm501_modify_reg(dev->parent, SM501_IRQ_MASK, 1 << 6, 0);

	return 0;
err4:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err3:
	usb_put_hcd(hcd);
err2:
	dma_release_declared_memory(dev);
err1:
	release_mem_region(mem->start, mem->end - mem->start + 1);
err0:
	return retval;
}