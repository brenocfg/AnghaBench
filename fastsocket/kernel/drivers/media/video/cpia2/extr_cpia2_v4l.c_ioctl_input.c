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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct camera_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 unsigned int VIDIOC_G_INPUT ; 
 int /*<<< orphan*/  memset (struct v4l2_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ioctl_input(unsigned int ioclt_nr,void *arg,struct camera_data *cam)
{
	struct v4l2_input *i = arg;

	if(ioclt_nr  != VIDIOC_G_INPUT) {
		if (i->index != 0)
		       return -EINVAL;
	}

	memset(i, 0, sizeof(*i));
	strcpy(i->name, "Camera");
	i->type = V4L2_INPUT_TYPE_CAMERA;

	return 0;
}