#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  readbuffers; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {TYPE_2__ parm; } ;
struct file {int dummy; } ;
struct cafe_camera {int /*<<< orphan*/  s_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_dma_bufs ; 
 int /*<<< orphan*/  s_parm ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int cafe_vidioc_s_parm(struct file *filp, void *priv,
		struct v4l2_streamparm *parms)
{
	struct cafe_camera *cam = priv;
	int ret;

	mutex_lock(&cam->s_mutex);
	ret = sensor_call(cam, video, s_parm, parms);
	mutex_unlock(&cam->s_mutex);
	parms->parm.capture.readbuffers = n_dma_bufs;
	return ret;
}