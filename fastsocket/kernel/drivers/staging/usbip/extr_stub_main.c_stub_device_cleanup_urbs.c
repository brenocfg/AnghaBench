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
struct urb {int /*<<< orphan*/ * setup_packet; int /*<<< orphan*/ * transfer_buffer; } ;
struct stub_priv {struct urb* urb; } ;
struct stub_device {int /*<<< orphan*/ * setup_packet; int /*<<< orphan*/ * transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stub_priv*) ; 
 int /*<<< orphan*/  stub_priv_cache ; 
 struct stub_priv* stub_priv_pop (struct urb*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usbip_udbg (char*,struct urb*) ; 

void stub_device_cleanup_urbs(struct stub_device *sdev)
{
	struct stub_priv *priv;

	usbip_udbg("free sdev %p\n", sdev);

	while ((priv = stub_priv_pop(sdev))) {
		struct urb *urb = priv->urb;

		usbip_udbg("   free urb %p\n", urb);
		usb_kill_urb(urb);

		kmem_cache_free(stub_priv_cache, priv);

		if (urb->transfer_buffer != NULL)
			kfree(urb->transfer_buffer);

		if (urb->setup_packet != NULL)
			kfree(urb->setup_packet);

		usb_free_urb(urb);
	}
}