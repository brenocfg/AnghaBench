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
struct v4l2_subdev {int /*<<< orphan*/  list; struct v4l2_device* v4l2_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  owner; int /*<<< orphan*/ * name; } ;
struct v4l2_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  subdevs; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int v4l2_device_register_subdev(struct v4l2_device *v4l2_dev,
						struct v4l2_subdev *sd)
{
	int err;

	/* Check for valid input */
	if (v4l2_dev == NULL || sd == NULL || !sd->name[0])
		return -EINVAL;
	/* Warn if we apparently re-register a subdev */
	WARN_ON(sd->v4l2_dev != NULL);
	if (!try_module_get(sd->owner))
		return -ENODEV;
	/* This just returns 0 if either of the two args is NULL */
	err = v4l2_ctrl_add_handler(v4l2_dev->ctrl_handler, sd->ctrl_handler);
	if (err)
		return err;
	sd->v4l2_dev = v4l2_dev;
	spin_lock(&v4l2_dev->lock);
	list_add_tail(&sd->list, &v4l2_dev->subdevs);
	spin_unlock(&v4l2_dev->lock);
	return 0;
}