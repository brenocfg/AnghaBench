#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dlfb_data {TYPE_1__* tx_urb; int /*<<< orphan*/  done; } ;
struct TYPE_3__ {int actual_length; int transfer_buffer_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dlfb_bulk_msg(struct dlfb_data *dev_info, int len)
{
	int ret;

	init_completion(&dev_info->done);

	dev_info->tx_urb->actual_length = 0;
	dev_info->tx_urb->transfer_buffer_length = len;

	ret = usb_submit_urb(dev_info->tx_urb, GFP_KERNEL);
	if (!wait_for_completion_timeout(&dev_info->done, 1000)) {
		usb_kill_urb(dev_info->tx_urb);
		printk("usb timeout !!!\n");
	}

	return dev_info->tx_urb->actual_length;
}