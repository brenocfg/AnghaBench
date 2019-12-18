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
struct ec168_req {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ec168_rw_udev (int /*<<< orphan*/ ,struct ec168_req*) ; 

__attribute__((used)) static int ec168_ctrl_msg(struct dvb_usb_device *d, struct ec168_req *req)
{
	return ec168_rw_udev(d->udev, req);
}