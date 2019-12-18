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
struct file {struct cafe_camera* private_data; } ;
struct cafe_camera {scalar_t__ users; int /*<<< orphan*/  s_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cafe_cam_reset (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_power_up (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_set_config_needed (struct cafe_camera*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cafe_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int cafe_v4l_open(struct file *filp)
{
	struct cafe_camera *cam = video_drvdata(filp);

	filp->private_data = cam;

	mutex_lock(&cam->s_mutex);
	if (cam->users == 0) {
		cafe_ctlr_power_up(cam);
		__cafe_cam_reset(cam);
		cafe_set_config_needed(cam, 1);
	/* FIXME make sure this is complete */
	}
	(cam->users)++;
	mutex_unlock(&cam->s_mutex);
	return 0;
}