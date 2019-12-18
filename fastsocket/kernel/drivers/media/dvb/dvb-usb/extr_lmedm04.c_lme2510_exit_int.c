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
struct lme2510_state {int i2c_talk_onoff; TYPE_1__* lme_urb; int /*<<< orphan*/  buffer; void* usb_buffer; scalar_t__ signal_sn; scalar_t__ signal_level; scalar_t__ signal_lock; } ;
struct dvb_usb_device {int /*<<< orphan*/  rc_dev; int /*<<< orphan*/  udev; struct dvb_usb_adapter* adapter; struct lme2510_state* priv; } ;
struct dvb_usb_adapter {scalar_t__ feedcount; int /*<<< orphan*/  stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  lme2510_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 

void *lme2510_exit_int(struct dvb_usb_device *d)
{
	struct lme2510_state *st = d->priv;
	struct dvb_usb_adapter *adap = &d->adapter[0];
	void *buffer = NULL;

	if (adap != NULL) {
		lme2510_kill_urb(&adap->stream);
		adap->feedcount = 0;
	}

	if (st->lme_urb != NULL) {
		st->i2c_talk_onoff = 1;
		st->signal_lock = 0;
		st->signal_level = 0;
		st->signal_sn = 0;
		buffer = st->usb_buffer;
		usb_kill_urb(st->lme_urb);
		usb_buffer_free(d->udev, 5000, st->buffer,
				  st->lme_urb->transfer_dma);
		info("Interupt Service Stopped");
		rc_unregister_device(d->rc_dev);
		info("Remote Stopped");
	}
	return buffer;
}