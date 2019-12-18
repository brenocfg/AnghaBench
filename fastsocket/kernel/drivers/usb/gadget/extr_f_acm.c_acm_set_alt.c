#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct TYPE_14__ {void* out_desc; void* in_desc; TYPE_2__* in; } ;
struct TYPE_12__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  notify; } ;
struct TYPE_11__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  notify; } ;
struct f_acm {unsigned int ctrl_id; unsigned int data_id; int /*<<< orphan*/  port_num; TYPE_7__ port; TYPE_4__ fs; TYPE_3__ hs; TYPE_5__* notify; void* notify_desc; } ;
struct TYPE_13__ {struct f_acm* driver_data; } ;
struct TYPE_10__ {scalar_t__ driver_data; } ;
struct TYPE_9__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,unsigned int) ; 
 void* ep_choose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_acm* func_to_acm (struct usb_function*) ; 
 int /*<<< orphan*/  gserial_connect (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gserial_disconnect (TYPE_7__*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_5__*) ; 
 int /*<<< orphan*/  usb_ep_enable (TYPE_5__*,void*) ; 

__attribute__((used)) static int acm_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_acm		*acm = func_to_acm(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	/* we know alt == 0, so this is an activation or a reset */

	if (intf == acm->ctrl_id) {
		if (acm->notify->driver_data) {
			VDBG(cdev, "reset acm control interface %d\n", intf);
			usb_ep_disable(acm->notify);
		} else {
			VDBG(cdev, "init acm ctrl interface %d\n", intf);
			acm->notify_desc = ep_choose(cdev->gadget,
					acm->hs.notify,
					acm->fs.notify);
		}
		usb_ep_enable(acm->notify, acm->notify_desc);
		acm->notify->driver_data = acm;

	} else if (intf == acm->data_id) {
		if (acm->port.in->driver_data) {
			DBG(cdev, "reset acm ttyGS%d\n", acm->port_num);
			gserial_disconnect(&acm->port);
		} else {
			DBG(cdev, "activate acm ttyGS%d\n", acm->port_num);
			acm->port.in_desc = ep_choose(cdev->gadget,
					acm->hs.in, acm->fs.in);
			acm->port.out_desc = ep_choose(cdev->gadget,
					acm->hs.out, acm->fs.out);
		}
		gserial_connect(&acm->port, acm->port_num);

	} else
		return -EINVAL;

	return 0;
}