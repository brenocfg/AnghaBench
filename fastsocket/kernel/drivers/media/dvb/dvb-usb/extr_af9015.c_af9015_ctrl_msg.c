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
struct req_t {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int af9015_rw_udev (int /*<<< orphan*/ ,struct req_t*) ; 

__attribute__((used)) static int af9015_ctrl_msg(struct dvb_usb_device *d, struct req_t *req)
{
	return af9015_rw_udev(d->udev, req);
}