#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {int is_dualspeed; int is_otg; TYPE_5__ dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct dummy {TYPE_2__ gadget; } ;
struct TYPE_9__ {scalar_t__ otg_port; } ;
struct TYPE_11__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_function ; 
 int /*<<< orphan*/  dev_set_name (TYPE_5__*,char*) ; 
 int device_create_file (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int device_register (TYPE_5__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_5__*) ; 
 int /*<<< orphan*/  dummy_gadget_release ; 
 int /*<<< orphan*/  dummy_ops ; 
 TYPE_3__* dummy_to_hcd (struct dummy*) ; 
 int /*<<< orphan*/  gadget_name ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dummy*) ; 
 struct dummy* the_controller ; 
 int /*<<< orphan*/  usb_get_hcd (TYPE_3__*) ; 

__attribute__((used)) static int dummy_udc_probe (struct platform_device *pdev)
{
	struct dummy	*dum = the_controller;
	int		rc;

	dum->gadget.name = gadget_name;
	dum->gadget.ops = &dummy_ops;
	dum->gadget.is_dualspeed = 1;

	/* maybe claim OTG support, though we won't complete HNP */
	dum->gadget.is_otg = (dummy_to_hcd(dum)->self.otg_port != 0);

	dev_set_name(&dum->gadget.dev, "gadget");
	dum->gadget.dev.parent = &pdev->dev;
	dum->gadget.dev.release = dummy_gadget_release;
	rc = device_register (&dum->gadget.dev);
	if (rc < 0)
		return rc;

	usb_get_hcd (dummy_to_hcd (dum));

	platform_set_drvdata (pdev, dum);
	rc = device_create_file (&dum->gadget.dev, &dev_attr_function);
	if (rc < 0)
		device_unregister (&dum->gadget.dev);
	return rc;
}