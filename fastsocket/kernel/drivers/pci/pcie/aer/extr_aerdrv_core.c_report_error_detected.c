#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_error_handlers {int /*<<< orphan*/  (* error_detected ) (struct pci_dev*,scalar_t__) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  sem; } ;
struct pci_dev {scalar_t__ error_state; int hdr_type; TYPE_2__ dev; TYPE_1__* driver; } ;
struct aer_broadcast_data {scalar_t__ state; int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
struct TYPE_3__ {struct pci_error_handlers* err_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NO_AER_DRIVER ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_io_frozen ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int report_error_detected(struct pci_dev *dev, void *data)
{
	pci_ers_result_t vote;
	const struct pci_error_handlers *err_handler;
	struct aer_broadcast_data *result_data;
	result_data = (struct aer_broadcast_data *) data;

	down(&dev->dev.sem);
	dev->error_state = result_data->state;

	if (!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->error_detected) {
		if (result_data->state == pci_channel_io_frozen &&
			!(dev->hdr_type & PCI_HEADER_TYPE_BRIDGE)) {
			/*
			 * In case of fatal recovery, if one of down-
			 * stream device has no driver. We might be
			 * unable to recover because a later insmod
			 * of a driver for this device is unaware of
			 * its hw state.
			 */
			dev_printk(KERN_DEBUG, &dev->dev, "device has %s\n",
				   dev->driver ?
				   "no AER-aware driver" : "no driver");
		}

		/*
		 * If there's any device in the subtree that does not
		 * have an error_detected callback, returning
		 * PCI_ERS_RESULT_NO_AER_DRIVER prevents calling of
		 * the subsequent mmio_enabled/slot_reset/resume
		 * callbacks of "any" device in the subtree. All the
		 * devices in the subtree are left in the error state
		 * without recovery.
		 */

		if (!(dev->hdr_type & PCI_HEADER_TYPE_BRIDGE))
			vote = PCI_ERS_RESULT_NO_AER_DRIVER;
		else
			vote = PCI_ERS_RESULT_NONE;
	} else {
		err_handler = dev->driver->err_handler;
		vote = err_handler->error_detected(dev, result_data->state);
	}

	result_data->result = merge_result(result_data->result, vote);
	up(&dev->dev.sem);
	return 0;
}