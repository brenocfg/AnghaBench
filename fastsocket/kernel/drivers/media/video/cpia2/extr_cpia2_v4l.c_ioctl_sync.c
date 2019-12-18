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
struct camera_data {int num_frames; } ;

/* Variables and functions */
 int EINVAL ; 
 int sync (struct camera_data*,int) ; 

__attribute__((used)) static int ioctl_sync(void *arg, struct camera_data *cam)
{
	int frame;

	frame = *(int*)arg;

	if (frame < 0 || frame >= cam->num_frames)
		return -EINVAL;

	return sync(cam, frame);
}