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
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int dummy; } ;
struct f_gser {int /*<<< orphan*/  port; int /*<<< orphan*/  port_num; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 struct f_gser* func_to_gser (struct usb_function*) ; 
 int /*<<< orphan*/  gserial_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gser_disable(struct usb_function *f)
{
	struct f_gser	*gser = func_to_gser(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "generic ttyGS%d deactivated\n", gser->port_num);
	gserial_disconnect(&gser->port);
}