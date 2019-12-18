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
struct TYPE_5__ {int caps; int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {struct dvb_usb_adapter* user_priv; int /*<<< orphan*/  complete; int /*<<< orphan*/  udev; } ;
struct dvb_usb_adapter {TYPE_2__ props; TYPE_3__ stream; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int DVB_USB_ADAP_RECEIVES_204_BYTE_TS ; 
 int /*<<< orphan*/  dvb_usb_data_complete ; 
 int /*<<< orphan*/  dvb_usb_data_complete_204 ; 
 int usb_urb_init (TYPE_3__*,int /*<<< orphan*/ *) ; 

int dvb_usb_adapter_stream_init(struct dvb_usb_adapter *adap)
{
	adap->stream.udev      = adap->dev->udev;
	if (adap->props.caps & DVB_USB_ADAP_RECEIVES_204_BYTE_TS)
		adap->stream.complete = dvb_usb_data_complete_204;
	else
	adap->stream.complete  = dvb_usb_data_complete;
	adap->stream.user_priv = adap;
	return usb_urb_init(&adap->stream, &adap->props.stream);
}