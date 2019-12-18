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
struct v4l2_frmsizeenum {int dummy; } ;
struct file {int dummy; } ;
struct cafe_camera {int /*<<< orphan*/  s_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  enum_framesizes ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frmsizeenum*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int cafe_vidioc_enum_framesizes(struct file *filp, void *priv,
		struct v4l2_frmsizeenum *sizes)
{
	struct cafe_camera *cam = priv;
	int ret;

	mutex_lock(&cam->s_mutex);
	ret = sensor_call(cam, video, enum_framesizes, sizes);
	mutex_unlock(&cam->s_mutex);
	return ret;
}