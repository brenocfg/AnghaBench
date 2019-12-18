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
struct usbhid_device {scalar_t__ urbout; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhid_restart_ctrl_queue (struct usbhid_device*) ; 
 int /*<<< orphan*/  usbhid_restart_out_queue (struct usbhid_device*) ; 

__attribute__((used)) static void usbhid_restart_queues(struct usbhid_device *usbhid)
{
	if (usbhid->urbout)
		usbhid_restart_out_queue(usbhid);
	usbhid_restart_ctrl_queue(usbhid);
}