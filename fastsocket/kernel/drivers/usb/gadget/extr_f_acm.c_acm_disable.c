#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int dummy; } ;
struct f_acm {TYPE_2__* notify; int /*<<< orphan*/  port; int /*<<< orphan*/  port_num; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver_data; } ;
struct TYPE_3__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 struct f_acm* func_to_acm (struct usb_function*) ; 
 int /*<<< orphan*/  gserial_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_2__*) ; 

__attribute__((used)) static void acm_disable(struct usb_function *f)
{
	struct f_acm	*acm = func_to_acm(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "acm ttyGS%d deactivated\n", acm->port_num);
	gserial_disconnect(&acm->port);
	usb_ep_disable(acm->notify);
	acm->notify->driver_data = NULL;
}