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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; } ;
struct snd_usb_midi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void free_urb_and_buffer(struct snd_usb_midi *umidi, struct urb *urb,
				unsigned int buffer_length)
{
	usb_buffer_free(umidi->dev, buffer_length,
			urb->transfer_buffer, urb->transfer_dma);
	usb_free_urb(urb);
}