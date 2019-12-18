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
struct usb_hcd {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct isp116x {int /*<<< orphan*/  addr_reg; int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct isp116x* hcd_to_isp116x (struct usb_hcd*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_debug_file (struct isp116x*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int isp116x_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct isp116x *isp116x;
	struct resource *res;

	if (!hcd)
		return 0;
	isp116x = hcd_to_isp116x(hcd);
	remove_debug_file(isp116x);
	usb_remove_hcd(hcd);

	iounmap(isp116x->data_reg);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	release_mem_region(res->start, 2);
	iounmap(isp116x->addr_reg);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, 2);

	usb_put_hcd(hcd);
	return 0;
}