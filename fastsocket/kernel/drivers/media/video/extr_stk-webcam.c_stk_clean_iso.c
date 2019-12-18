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
struct urb {int dummy; } ;
struct stk_camera {TYPE_1__* isobufs; int /*<<< orphan*/  urbs_used; } ;
struct TYPE_2__ {struct TYPE_2__* data; struct urb* urb; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  unset_memallocd (struct stk_camera*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void stk_clean_iso(struct stk_camera *dev)
{
	int i;

	if (dev == NULL || dev->isobufs == NULL)
		return;

	for (i = 0; i < MAX_ISO_BUFS; i++) {
		struct urb *urb;

		urb = dev->isobufs[i].urb;
		if (urb) {
			if (atomic_read(&dev->urbs_used) && is_present(dev))
				usb_kill_urb(urb);
			usb_free_urb(urb);
		}
		kfree(dev->isobufs[i].data);
	}
	kfree(dev->isobufs);
	dev->isobufs = NULL;
	unset_memallocd(dev);
}