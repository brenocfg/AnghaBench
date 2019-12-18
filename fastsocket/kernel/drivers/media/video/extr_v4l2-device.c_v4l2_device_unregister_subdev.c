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
struct v4l2_subdev {int /*<<< orphan*/  owner; TYPE_1__* v4l2_dev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void v4l2_device_unregister_subdev(struct v4l2_subdev *sd)
{
	/* return if it isn't registered */
	if (sd == NULL || sd->v4l2_dev == NULL)
		return;
	spin_lock(&sd->v4l2_dev->lock);
	list_del(&sd->list);
	spin_unlock(&sd->v4l2_dev->lock);
	sd->v4l2_dev = NULL;
	module_put(sd->owner);
}