#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct TYPE_11__ {void* out_desc; void* in_desc; TYPE_2__* in; } ;
struct TYPE_10__ {int /*<<< orphan*/  obex_out; int /*<<< orphan*/  obex_in; } ;
struct TYPE_9__ {int /*<<< orphan*/  obex_out; int /*<<< orphan*/  obex_in; } ;
struct f_obex {unsigned int ctrl_id; unsigned int data_id; int /*<<< orphan*/  port_num; TYPE_5__ port; TYPE_4__ fs; TYPE_3__ hs; } ;
struct TYPE_8__ {scalar_t__ driver_data; } ;
struct TYPE_7__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 void* ep_choose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_obex* func_to_obex (struct usb_function*) ; 
 int /*<<< orphan*/  gserial_connect (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gserial_disconnect (TYPE_5__*) ; 

__attribute__((used)) static int obex_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_obex		*obex = func_to_obex(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	if (intf == obex->ctrl_id) {
		if (alt != 0)
			goto fail;
		/* NOP */
		DBG(cdev, "reset obex ttyGS%d control\n", obex->port_num);

	} else if (intf == obex->data_id) {
		if (alt > 1)
			goto fail;

		if (obex->port.in->driver_data) {
			DBG(cdev, "reset obex ttyGS%d\n", obex->port_num);
			gserial_disconnect(&obex->port);
		}

		if (!obex->port.in_desc) {
			DBG(cdev, "init obex ttyGS%d\n", obex->port_num);
			obex->port.in_desc = ep_choose(cdev->gadget,
					obex->hs.obex_in, obex->fs.obex_in);
			obex->port.out_desc = ep_choose(cdev->gadget,
					obex->hs.obex_out, obex->fs.obex_out);
		}

		if (alt == 1) {
			DBG(cdev, "activate obex ttyGS%d\n", obex->port_num);
			gserial_connect(&obex->port, obex->port_num);
		}

	} else
		goto fail;

	return 0;

fail:
	return -EINVAL;
}