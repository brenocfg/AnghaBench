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
struct usb_sg_request {size_t entries; TYPE_2__* dev; int /*<<< orphan*/  nents; int /*<<< orphan*/  sg; int /*<<< orphan*/  pipe; int /*<<< orphan*/ * urbs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dma_mask; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_unmap_sg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sg_clean(struct usb_sg_request *io)
{
	if (io->urbs) {
		while (io->entries--)
			usb_free_urb(io->urbs [io->entries]);
		kfree(io->urbs);
		io->urbs = NULL;
	}
	if (io->dev->dev.dma_mask != NULL)
		usb_buffer_unmap_sg(io->dev, usb_pipein(io->pipe),
				    io->sg, io->nents);
	io->dev = NULL;
}