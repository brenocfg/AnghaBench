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
struct ttusb {int /*<<< orphan*/  iso_dma_handle; int /*<<< orphan*/  iso_buffer; scalar_t__* iso_urb; } ;

/* Variables and functions */
 int FRAMES_PER_ISO_BUF ; 
 int ISO_BUF_COUNT ; 
 int ISO_FRAME_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 

__attribute__((used)) static void ttusb_free_iso_urbs(struct ttusb *ttusb)
{
	int i;

	for (i = 0; i < ISO_BUF_COUNT; i++)
		if (ttusb->iso_urb[i])
			usb_free_urb(ttusb->iso_urb[i]);

	pci_free_consistent(NULL,
			    ISO_FRAME_SIZE * FRAMES_PER_ISO_BUF *
			    ISO_BUF_COUNT, ttusb->iso_buffer,
			    ttusb->iso_dma_handle);
}