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
struct v4l2_queryctrl {int dummy; } ;
struct file {int dummy; } ;
struct cafe_camera {int /*<<< orphan*/  s_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queryctrl ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int cafe_vidioc_queryctrl(struct file *filp, void *priv,
		struct v4l2_queryctrl *qc)
{
	struct cafe_camera *cam = priv;
	int ret;

	mutex_lock(&cam->s_mutex);
	ret = sensor_call(cam, core, queryctrl, qc);
	mutex_unlock(&cam->s_mutex);
	return ret;
}