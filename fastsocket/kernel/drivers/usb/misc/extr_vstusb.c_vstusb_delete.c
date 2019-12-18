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
struct vstusb_device {int /*<<< orphan*/  usb_dev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vstusb_device*) ; 
 struct vstusb_device* to_vst_dev (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vstusb_delete(struct kref *kref)
{
	struct vstusb_device *vstdev = to_vst_dev(kref);

	usb_put_dev(vstdev->usb_dev);
	kfree(vstdev);
}