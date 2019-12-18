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
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/  regs; } ;
struct platform_device {int num_resources; TYPE_1__* resource; int /*<<< orphan*/  dev; } ;
struct hc_driver {int dummy; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IORESOURCE_IRQ ; 
 scalar_t__ IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  at91_start_hc (struct platform_device*) ; 
 int /*<<< orphan*/  at91_stop_hc (struct platform_device*) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_at91sam9261 () ; 
 int /*<<< orphan*/  fclk ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  hclk ; 
 int /*<<< orphan*/  iclk ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_hcd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int usb_add_hcd (struct usb_hcd*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int usb_hcd_at91_probe(const struct hc_driver *driver,
			struct platform_device *pdev)
{
	int retval;
	struct usb_hcd *hcd = NULL;

	if (pdev->num_resources != 2) {
		pr_debug("hcd probe: invalid num_resources");
		return -ENODEV;
	}

	if ((pdev->resource[0].flags != IORESOURCE_MEM)
			|| (pdev->resource[1].flags != IORESOURCE_IRQ)) {
		pr_debug("hcd probe: invalid resource type\n");
		return -ENODEV;
	}

	hcd = usb_create_hcd(driver, &pdev->dev, "at91");
	if (!hcd)
		return -ENOMEM;
	hcd->rsrc_start = pdev->resource[0].start;
	hcd->rsrc_len = pdev->resource[0].end - pdev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		pr_debug("request_mem_region failed\n");
		retval = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		pr_debug("ioremap failed\n");
		retval = -EIO;
		goto err2;
	}

	iclk = clk_get(&pdev->dev, "ohci_clk");
	fclk = clk_get(&pdev->dev, "uhpck");
	if (cpu_is_at91sam9261())
		hclk = clk_get(&pdev->dev, "hck0");

	at91_start_hc(pdev);
	ohci_hcd_init(hcd_to_ohci(hcd));

	retval = usb_add_hcd(hcd, pdev->resource[1].start, IRQF_SHARED);
	if (retval == 0)
		return retval;

	/* Error handling */
	at91_stop_hc(pdev);

	if (cpu_is_at91sam9261())
		clk_put(hclk);
	clk_put(fclk);
	clk_put(iclk);

	iounmap(hcd->regs);

 err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);

 err1:
	usb_put_hcd(hcd);
	return retval;
}