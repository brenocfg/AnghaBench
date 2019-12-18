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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MJPEG ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *fmt)
{
	char *desc = NULL;

	switch (fmt->index) {
	case 0:
		fmt->pixelformat = V4L2_PIX_FMT_MJPEG;
		desc = "Motion-JPEG";
		break;
	case 1:
		fmt->pixelformat = V4L2_PIX_FMT_MPEG;
		desc = "MPEG1/MPEG2/MPEG4";
		break;
	default:
		return -EINVAL;
	}
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->flags = V4L2_FMT_FLAG_COMPRESSED;

	strncpy(fmt->description, desc, sizeof(fmt->description));

	return 0;
}