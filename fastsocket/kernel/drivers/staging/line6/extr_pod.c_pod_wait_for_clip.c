#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ value; int /*<<< orphan*/  wait; } ;
struct usb_line6_pod {TYPE_1__ clipping; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_line6_pod* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t pod_wait_for_clip(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6_pod *pod = usb_get_intfdata(interface);
	int err = 0;
	DECLARE_WAITQUEUE(wait, current);
	pod->clipping.value = 0;
	add_wait_queue(&pod->clipping.wait, &wait);
	current->state = TASK_INTERRUPTIBLE;

	while (pod->clipping.value == 0) {
		if (signal_pending(current)) {
			err = -ERESTARTSYS;
			break;
		} else
			schedule();
	}

	current->state = TASK_RUNNING;
	remove_wait_queue(&pod->clipping.wait, &wait);
	return err;
}