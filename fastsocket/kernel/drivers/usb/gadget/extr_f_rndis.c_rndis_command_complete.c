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
typedef  int /*<<< orphan*/  u8 ;
struct usb_request {int /*<<< orphan*/  length; int /*<<< orphan*/  actual; scalar_t__ buf; struct f_rndis* context; } ;
struct usb_ep {int dummy; } ;
struct usb_composite_dev {int dummy; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_6__ {TYPE_2__ func; } ;
struct f_rndis {int /*<<< orphan*/  config; TYPE_3__ port; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rndis_msg_parser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rndis_command_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct f_rndis			*rndis = req->context;
	struct usb_composite_dev	*cdev = rndis->port.func.config->cdev;
	int				status;

	/* received RNDIS command from USB_CDC_SEND_ENCAPSULATED_COMMAND */
//	spin_lock(&dev->lock);
	status = rndis_msg_parser(rndis->config, (u8 *) req->buf);
	if (status < 0)
		ERROR(cdev, "RNDIS command error %d, %d/%d\n",
			status, req->actual, req->length);
//	spin_unlock(&dev->lock);
}