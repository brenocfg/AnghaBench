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
struct pci_driver {TYPE_1__* err_handler; } ;
struct pci_dev {int /*<<< orphan*/  error_state; struct pci_driver* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  eeh_enable_irq (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static int eeh_report_resume(struct pci_dev *dev, void *userdata)
{
	struct pci_driver *driver = dev->driver;

	dev->error_state = pci_channel_io_normal;

	if (!driver)
		return 0;

	eeh_enable_irq(dev);

	if (!driver->err_handler ||
	    !driver->err_handler->resume)
		return 0;

	driver->err_handler->resume(dev);

	return 0;
}