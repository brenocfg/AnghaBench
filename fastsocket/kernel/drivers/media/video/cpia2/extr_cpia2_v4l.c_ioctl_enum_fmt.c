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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct camera_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MJPEG ; 
 int /*<<< orphan*/  memset (struct v4l2_fmtdesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ioctl_enum_fmt(void *arg,struct camera_data *cam)
{
	struct v4l2_fmtdesc *f = arg;
	int index = f->index;

	if (index < 0 || index > 1)
	       return -EINVAL;

	memset(f, 0, sizeof(*f));
	f->index = index;
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	f->flags = V4L2_FMT_FLAG_COMPRESSED;
	switch(index) {
	case 0:
		strcpy(f->description, "MJPEG");
		f->pixelformat = V4L2_PIX_FMT_MJPEG;
		break;
	case 1:
		strcpy(f->description, "JPEG");
		f->pixelformat = V4L2_PIX_FMT_JPEG;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}