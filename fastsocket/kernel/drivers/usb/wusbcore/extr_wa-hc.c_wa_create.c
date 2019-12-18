#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wahc {int /*<<< orphan*/ * xfer_result; int /*<<< orphan*/  xfer_result_size; TYPE_3__* dti_epd; TYPE_3__* dto_epd; } ;
struct device {int dummy; } ;
struct usb_interface {TYPE_2__* cur_altsetting; struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_5__ {TYPE_1__* endpoint; } ;
struct TYPE_4__ {TYPE_3__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int wa_nep_create (struct wahc*,struct usb_interface*) ; 
 int wa_rpipes_create (struct wahc*) ; 
 int /*<<< orphan*/  wa_rpipes_destroy (struct wahc*) ; 

int wa_create(struct wahc *wa, struct usb_interface *iface)
{
	int result;
	struct device *dev = &iface->dev;

	result = wa_rpipes_create(wa);
	if (result < 0)
		goto error_rpipes_create;
	/* Fill up Data Transfer EP pointers */
	wa->dti_epd = &iface->cur_altsetting->endpoint[1].desc;
	wa->dto_epd = &iface->cur_altsetting->endpoint[2].desc;
	wa->xfer_result_size = le16_to_cpu(wa->dti_epd->wMaxPacketSize);
	wa->xfer_result = kmalloc(wa->xfer_result_size, GFP_KERNEL);
	if (wa->xfer_result == NULL)
		goto error_xfer_result_alloc;
	result = wa_nep_create(wa, iface);
	if (result < 0) {
		dev_err(dev, "WA-CDS: can't initialize notif endpoint: %d\n",
			result);
		goto error_nep_create;
	}
	return 0;

error_nep_create:
	kfree(wa->xfer_result);
error_xfer_result_alloc:
	wa_rpipes_destroy(wa);
error_rpipes_create:
	return result;
}