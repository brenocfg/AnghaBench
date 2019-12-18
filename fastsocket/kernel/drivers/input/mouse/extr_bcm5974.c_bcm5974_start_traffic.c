#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bcm5974 {int /*<<< orphan*/  bt_urb; int /*<<< orphan*/  tp_urb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bcm5974_wellspring_mode (struct bcm5974*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm5974_start_traffic(struct bcm5974 *dev)
{
	if (bcm5974_wellspring_mode(dev, true)) {
		dprintk(1, "bcm5974: mode switch failed\n");
		goto error;
	}

	if (usb_submit_urb(dev->bt_urb, GFP_KERNEL))
		goto error;

	if (usb_submit_urb(dev->tp_urb, GFP_KERNEL))
		goto err_kill_bt;

	return 0;

err_kill_bt:
	usb_kill_urb(dev->bt_urb);
error:
	return -EIO;
}