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
struct comedi_driver {int (* attach ) (struct comedi_device*,struct comedi_devconfig*) ;int /*<<< orphan*/  module; struct comedi_driver* next; int /*<<< orphan*/  driver_name; scalar_t__ num_names; } ;
struct comedi_device {int attached; char* board_name; struct comedi_driver* driver; int /*<<< orphan*/ * board_ptr; } ;
struct comedi_devconfig {int /*<<< orphan*/  board_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  __comedi_device_detach (struct comedi_device*) ; 
 struct comedi_driver* comedi_drivers ; 
 int /*<<< orphan*/ * comedi_recognize (struct comedi_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_report_boards (struct comedi_driver*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int postconfig (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int comedi_device_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_driver *driv;
	int ret;

	if (dev->attached)
		return -EBUSY;

	for (driv = comedi_drivers; driv; driv = driv->next) {
		if (!try_module_get(driv->module)) {
			printk
			    ("comedi: failed to increment module count, skipping\n");
			continue;
		}
		if (driv->num_names) {
			dev->board_ptr = comedi_recognize(driv, it->board_name);
			if (dev->board_ptr == NULL) {
				module_put(driv->module);
				continue;
			}
		} else {
			if (strcmp(driv->driver_name, it->board_name)) {
				module_put(driv->module);
				continue;
			}
		}
		/* initialize dev->driver here so comedi_error() can be called from attach */
		dev->driver = driv;
		ret = driv->attach(dev, it);
		if (ret < 0) {
			module_put(dev->driver->module);
			__comedi_device_detach(dev);
			return ret;
		}
		goto attached;
	}

	/*  recognize has failed if we get here */
	/*  report valid board names before returning error */
	for (driv = comedi_drivers; driv; driv = driv->next) {
		if (!try_module_get(driv->module)) {
			printk("comedi: failed to increment module count\n");
			continue;
		}
		comedi_report_boards(driv);
		module_put(driv->module);
	}
	return -EIO;

attached:
	/* do a little post-config cleanup */
	ret = postconfig(dev);
	module_put(dev->driver->module);
	if (ret < 0) {
		__comedi_device_detach(dev);
		return ret;
	}

	if (!dev->board_name) {
		printk("BUG: dev->board_name=<%p>\n", dev->board_name);
		dev->board_name = "BUG";
	}
	smp_wmb();
	dev->attached = 1;

	return 0;
}