#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lme2510_state {TYPE_2__* lme_urb; int /*<<< orphan*/ * buffer; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  udev; struct lme2510_state* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  lme2510_int_response ; 
 TYPE_2__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usb_buffer_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dvb_usb_adapter*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lme2510_int_read(struct dvb_usb_adapter *adap)
{
	struct lme2510_state *lme_int = adap->dev->priv;

	lme_int->lme_urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (lme_int->lme_urb == NULL)
			return -ENOMEM;

	lme_int->buffer = usb_buffer_alloc(adap->dev->udev, 5000, GFP_ATOMIC,
					&lme_int->lme_urb->transfer_dma);

	if (lme_int->buffer == NULL)
			return -ENOMEM;

	usb_fill_int_urb(lme_int->lme_urb,
				adap->dev->udev,
				usb_rcvintpipe(adap->dev->udev, 0xa),
				lme_int->buffer,
				4096,
				lme2510_int_response,
				adap,
				11);

	lme_int->lme_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_submit_urb(lme_int->lme_urb, GFP_ATOMIC);
	info("INT Interupt Service Started");

	return 0;
}