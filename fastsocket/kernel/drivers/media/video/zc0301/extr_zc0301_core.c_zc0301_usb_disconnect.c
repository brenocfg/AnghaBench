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
struct zc0301_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  wait_open; int /*<<< orphan*/  state; int /*<<< orphan*/  wait_stream; int /*<<< orphan*/  wait_frame; TYPE_1__* v4ldev; scalar_t__ users; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  DEV_MISCONFIGURED ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct zc0301_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zc0301_dev_lock ; 
 int /*<<< orphan*/  zc0301_release_resources ; 
 int /*<<< orphan*/  zc0301_stop_transfer (struct zc0301_device*) ; 

__attribute__((used)) static void zc0301_usb_disconnect(struct usb_interface* intf)
{
	struct zc0301_device* cam;

	down_write(&zc0301_dev_lock);

	cam = usb_get_intfdata(intf);

	DBG(2, "Disconnecting %s...", cam->v4ldev->name);

	if (cam->users) {
		DBG(2, "Device /dev/video%d is open! Deregistration and "
		       "memory deallocation are deferred.",
		    cam->v4ldev->num);
		cam->state |= DEV_MISCONFIGURED;
		zc0301_stop_transfer(cam);
		cam->state |= DEV_DISCONNECTED;
		wake_up_interruptible(&cam->wait_frame);
		wake_up(&cam->wait_stream);
	} else
		cam->state |= DEV_DISCONNECTED;

	wake_up_interruptible_all(&cam->wait_open);

	kref_put(&cam->kref, zc0301_release_resources);

	up_write(&zc0301_dev_lock);
}