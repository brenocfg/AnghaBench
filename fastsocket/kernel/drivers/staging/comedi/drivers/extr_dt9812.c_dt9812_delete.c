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
struct usb_dt9812 {int /*<<< orphan*/  udev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_dt9812*) ; 
 struct usb_dt9812* to_dt9812_dev (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dt9812_delete(struct kref *kref)
{
	struct usb_dt9812 *dev = to_dt9812_dev(kref);

	usb_put_dev(dev->udev);
	kfree(dev);
}