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
struct ccw_device {int dummy; } ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_UNREG ; 
 int /*<<< orphan*/  CIO_GONE ; 
 scalar_t__ NOTIFY_OK ; 
 scalar_t__ ccw_device_notify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_disconnected (struct ccw_device*) ; 

__attribute__((used)) static void ccw_device_generic_notoper(struct ccw_device *cdev,
				       enum dev_event dev_event)
{
	if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
		ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
	else
		ccw_device_set_disconnected(cdev);
}