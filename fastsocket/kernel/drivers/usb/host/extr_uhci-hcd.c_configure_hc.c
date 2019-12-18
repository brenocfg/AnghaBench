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
struct uhci_hcd {int frame_number; scalar_t__ io_addr; int /*<<< orphan*/  frame_dma_handle; } ;

/* Variables and functions */
 int UHCI_MAX_SOF_NUMBER ; 
 scalar_t__ USBFLBASEADD ; 
 scalar_t__ USBFRNUM ; 
 int /*<<< orphan*/  USBLEGSUP ; 
 int /*<<< orphan*/  USBLEGSUP_DEFAULT ; 
 scalar_t__ USBSOF ; 
 int /*<<< orphan*/  USBSOF_DEFAULT ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 

__attribute__((used)) static void configure_hc(struct uhci_hcd *uhci)
{
	/* Set the frame length to the default: 1 ms exactly */
	outb(USBSOF_DEFAULT, uhci->io_addr + USBSOF);

	/* Store the frame list base address */
	outl(uhci->frame_dma_handle, uhci->io_addr + USBFLBASEADD);

	/* Set the current frame number */
	outw(uhci->frame_number & UHCI_MAX_SOF_NUMBER,
			uhci->io_addr + USBFRNUM);

	/* Enable PIRQ */
	pci_write_config_word(to_pci_dev(uhci_dev(uhci)), USBLEGSUP,
			USBLEGSUP_DEFAULT);
}