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
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int dummy; } ;
struct TYPE_6__ {TYPE_2__* in_ep; } ;
struct f_eem {TYPE_3__ port; } ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 struct f_eem* func_to_eem (struct usb_function*) ; 
 int /*<<< orphan*/  gether_disconnect (TYPE_3__*) ; 

__attribute__((used)) static void eem_disable(struct usb_function *f)
{
	struct f_eem		*eem = func_to_eem(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "eem deactivated\n");

	if (eem->port.in_ep->driver_data)
		gether_disconnect(&eem->port);
}