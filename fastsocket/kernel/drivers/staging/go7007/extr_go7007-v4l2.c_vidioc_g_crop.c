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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_crop {scalar_t__ type; TYPE_1__ c; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int standard; TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int sensor_width; int sensor_height; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GO7007_STD_NTSC 130 
#define  GO7007_STD_OTHER 129 
#define  GO7007_STD_PAL 128 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int vidioc_g_crop(struct file *file, void *priv, struct v4l2_crop *crop)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	crop->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	/* These specify the raw input of the sensor */
	switch (go->standard) {
	case GO7007_STD_NTSC:
		crop->c.top = 0;
		crop->c.left = 0;
		crop->c.width = 720;
		crop->c.height = 480;
		break;
	case GO7007_STD_PAL:
		crop->c.top = 0;
		crop->c.left = 0;
		crop->c.width = 720;
		crop->c.height = 576;
		break;
	case GO7007_STD_OTHER:
		crop->c.top = 0;
		crop->c.left = 0;
		crop->c.width = go->board_info->sensor_width;
		crop->c.height = go->board_info->sensor_height;
		break;
	}

	return 0;
}