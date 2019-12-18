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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 int AER_FATAL ; 
 scalar_t__ PCI_ERS_RESULT_CAN_RECOVER ; 
 scalar_t__ PCI_ERS_RESULT_NEED_RESET ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ broadcast_error_message (struct pci_dev*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int pci_channel_io_frozen ; 
 int pci_channel_io_normal ; 
 int /*<<< orphan*/  report_error_detected ; 
 int /*<<< orphan*/  report_mmio_enabled ; 
 int /*<<< orphan*/  report_resume ; 
 int /*<<< orphan*/  report_slot_reset ; 
 scalar_t__ reset_link (struct pci_dev*) ; 

__attribute__((used)) static void do_recovery(struct pci_dev *dev, int severity)
{
	pci_ers_result_t status, result = PCI_ERS_RESULT_RECOVERED;
	enum pci_channel_state state;

	if (severity == AER_FATAL)
		state = pci_channel_io_frozen;
	else
		state = pci_channel_io_normal;

	status = broadcast_error_message(dev,
			state,
			"error_detected",
			report_error_detected);

	if (severity == AER_FATAL) {
		result = reset_link(dev);
		if (result != PCI_ERS_RESULT_RECOVERED)
			goto failed;
	}

	if (status == PCI_ERS_RESULT_CAN_RECOVER)
		status = broadcast_error_message(dev,
				state,
				"mmio_enabled",
				report_mmio_enabled);

	if (status == PCI_ERS_RESULT_NEED_RESET) {
		/*
		 * TODO: Should call platform-specific
		 * functions to reset slot before calling
		 * drivers' slot_reset callbacks?
		 */
		status = broadcast_error_message(dev,
				state,
				"slot_reset",
				report_slot_reset);
	}

	if (status != PCI_ERS_RESULT_RECOVERED)
		goto failed;

	broadcast_error_message(dev,
				state,
				"resume",
				report_resume);

	dev_info(&dev->dev, "AER Device recovery successful\n");
	return;

failed:
	/* TODO: Should kernel panic here? */
	dev_info(&dev->dev, "AER Device recovery failed\n");
}