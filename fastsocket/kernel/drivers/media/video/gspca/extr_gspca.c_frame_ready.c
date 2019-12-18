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
struct gspca_dev {int /*<<< orphan*/  queue_lock; } ;
struct file {int dummy; } ;
typedef  enum v4l2_memory { ____Placeholder_v4l2_memory } v4l2_memory ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int frame_ready_nolock (struct gspca_dev*,struct file*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int frame_ready(struct gspca_dev *gspca_dev, struct file *file,
			enum v4l2_memory memory)
{
	int ret;

	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;
	ret = frame_ready_nolock(gspca_dev, file, memory);
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}