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
struct TYPE_10__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct f_gser {int /*<<< orphan*/  port_num; TYPE_5__ port; TYPE_4__ fs; TYPE_3__ hs; } ;
struct TYPE_8__ {scalar_t__ driver_data; } ;
struct TYPE_7__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 void* ep_choose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_gser* func_to_gser (struct usb_function*) ; 
 int /*<<< orphan*/  gserial_connect (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gserial_disconnect (TYPE_5__*) ; 

__attribute__((used)) static int gser_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_gser		*gser = func_to_gser(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	/* we know alt == 0, so this is an activation or a reset */

	if (gser->port.in->driver_data) {
		DBG(cdev, "reset generic ttyGS%d\n", gser->port_num);
		gserial_disconnect(&gser->port);
	} else {
		DBG(cdev, "activate generic ttyGS%d\n", gser->port_num);
		gser->port.in_desc = ep_choose(cdev->gadget,
				gser->hs.in, gser->fs.in);
		gser->port.out_desc = ep_choose(cdev->gadget,
				gser->hs.out, gser->fs.out);
	}
	gserial_connect(&gser->port, gser->port_num);
	return 0;
}