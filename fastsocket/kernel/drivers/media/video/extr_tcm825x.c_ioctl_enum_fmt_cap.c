#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_int_device {int dummy; } ;
struct v4l2_fmtdesc {int index; int type; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCM825X_NUM_CAPTURE_FORMATS ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tcm825x_formats ; 

__attribute__((used)) static int ioctl_enum_fmt_cap(struct v4l2_int_device *s,
				   struct v4l2_fmtdesc *fmt)
{
	int index = fmt->index;

	switch (fmt->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		if (index >= TCM825X_NUM_CAPTURE_FORMATS)
			return -EINVAL;
		break;

	default:
		return -EINVAL;
	}

	fmt->flags = tcm825x_formats[index].flags;
	strlcpy(fmt->description, tcm825x_formats[index].description,
		sizeof(fmt->description));
	fmt->pixelformat = tcm825x_formats[index].pixelformat;

	return 0;
}