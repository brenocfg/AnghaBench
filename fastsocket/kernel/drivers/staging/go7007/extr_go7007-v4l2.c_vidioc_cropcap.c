#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ defrect; TYPE_1__ bounds; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int standard; TYPE_3__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int sensor_width; int sensor_height; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GO7007_STD_NTSC 130 
#define  GO7007_STD_OTHER 129 
#define  GO7007_STD_PAL 128 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int vidioc_cropcap(struct file *file, void *priv,
					struct v4l2_cropcap *cropcap)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (cropcap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	/* These specify the raw input of the sensor */
	switch (go->standard) {
	case GO7007_STD_NTSC:
		cropcap->bounds.top = 0;
		cropcap->bounds.left = 0;
		cropcap->bounds.width = 720;
		cropcap->bounds.height = 480;
		cropcap->defrect.top = 0;
		cropcap->defrect.left = 0;
		cropcap->defrect.width = 720;
		cropcap->defrect.height = 480;
		break;
	case GO7007_STD_PAL:
		cropcap->bounds.top = 0;
		cropcap->bounds.left = 0;
		cropcap->bounds.width = 720;
		cropcap->bounds.height = 576;
		cropcap->defrect.top = 0;
		cropcap->defrect.left = 0;
		cropcap->defrect.width = 720;
		cropcap->defrect.height = 576;
		break;
	case GO7007_STD_OTHER:
		cropcap->bounds.top = 0;
		cropcap->bounds.left = 0;
		cropcap->bounds.width = go->board_info->sensor_width;
		cropcap->bounds.height = go->board_info->sensor_height;
		cropcap->defrect.top = 0;
		cropcap->defrect.left = 0;
		cropcap->defrect.width = go->board_info->sensor_width;
		cropcap->defrect.height = go->board_info->sensor_height;
		break;
	}

	return 0;
}