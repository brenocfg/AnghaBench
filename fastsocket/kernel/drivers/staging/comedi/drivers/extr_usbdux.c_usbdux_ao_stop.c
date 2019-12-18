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
struct usbduxsub {scalar_t__ ao_cmd_running; TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int usbduxsub_unlink_OutURBs (struct usbduxsub*) ; 

__attribute__((used)) static int usbdux_ao_stop(struct usbduxsub *this_usbduxsub, int do_unlink)
{
	int ret = 0;

	if (!this_usbduxsub)
		return -EFAULT;
	dev_dbg(&this_usbduxsub->interface->dev, "comedi: usbdux_ao_cancel\n");

	if (do_unlink)
		ret = usbduxsub_unlink_OutURBs(this_usbduxsub);

	this_usbduxsub->ao_cmd_running = 0;

	return ret;
}