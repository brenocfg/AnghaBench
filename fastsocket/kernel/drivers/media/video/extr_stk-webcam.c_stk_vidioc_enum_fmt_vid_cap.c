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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  description; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB565 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB565X ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stk_vidioc_enum_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_fmtdesc *fmtd)
{
	switch (fmtd->index) {
	case 0:
		fmtd->pixelformat = V4L2_PIX_FMT_RGB565;
		strcpy(fmtd->description, "r5g6b5");
		break;
	case 1:
		fmtd->pixelformat = V4L2_PIX_FMT_RGB565X;
		strcpy(fmtd->description, "r5g6b5BE");
		break;
	case 2:
		fmtd->pixelformat = V4L2_PIX_FMT_UYVY;
		strcpy(fmtd->description, "yuv4:2:2");
		break;
	case 3:
		fmtd->pixelformat = V4L2_PIX_FMT_SBGGR8;
		strcpy(fmtd->description, "Raw bayer");
		break;
	case 4:
		fmtd->pixelformat = V4L2_PIX_FMT_YUYV;
		strcpy(fmtd->description, "yuv4:2:2");
		break;
	default:
		return -EINVAL;
	}
	return 0;
}