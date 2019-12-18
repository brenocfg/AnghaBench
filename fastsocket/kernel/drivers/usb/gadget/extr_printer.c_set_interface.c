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
struct printer_dev {int interface; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int /*<<< orphan*/  INFO (struct printer_dev*,char*,...) ; 
#define  PRINTER_INTERFACE 128 
 scalar_t__ gadget_is_sa1100 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printer_reset_interface (struct printer_dev*) ; 
 int set_printer_interface (struct printer_dev*) ; 

__attribute__((used)) static int
set_interface(struct printer_dev *dev, unsigned number)
{
	int			result = 0;

	if (gadget_is_sa1100(dev->gadget) && dev->interface < 0) {
		/* tx fifo is full, but we can't clear it...*/
		INFO(dev, "can't change interfaces\n");
		return -ESPIPE;
	}

	/* Free the current interface */
	switch (dev->interface) {
	case PRINTER_INTERFACE:
		printer_reset_interface(dev);
		break;
	}

	switch (number) {
	case PRINTER_INTERFACE:
		result = set_printer_interface(dev);
		if (result) {
			printer_reset_interface(dev);
		} else {
			dev->interface = PRINTER_INTERFACE;
		}
		break;
	default:
		result = -EINVAL;
		/* FALL THROUGH */
	}

	if (!result)
		INFO(dev, "Using interface %x\n", number);

	return result;
}