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
struct v4l2_ioctl_ops {int /*<<< orphan*/  vidioc_g_fmt_type_private; int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_out; int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_cap; int /*<<< orphan*/  vidioc_g_fmt_vbi_out; int /*<<< orphan*/  vidioc_g_fmt_vbi_cap; int /*<<< orphan*/  vidioc_g_fmt_vid_out_overlay; int /*<<< orphan*/  vidioc_g_fmt_vid_out; int /*<<< orphan*/  vidioc_g_fmt_vid_overlay; int /*<<< orphan*/  vidioc_g_fmt_vid_cap; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_PRIVATE 136 
#define  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE 135 
#define  V4L2_BUF_TYPE_SLICED_VBI_OUTPUT 134 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 133 
#define  V4L2_BUF_TYPE_VBI_OUTPUT 132 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY 129 
#define  V4L2_BUF_TYPE_VIDEO_OVERLAY 128 

__attribute__((used)) static int check_fmt(const struct v4l2_ioctl_ops *ops, enum v4l2_buf_type type)
{
	if (ops == NULL)
		return -EINVAL;

	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		if (ops->vidioc_g_fmt_vid_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
		if (ops->vidioc_g_fmt_vid_overlay)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		if (ops->vidioc_g_fmt_vid_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		if (ops->vidioc_g_fmt_vid_out_overlay)
			return 0;
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		if (ops->vidioc_g_fmt_vbi_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		if (ops->vidioc_g_fmt_vbi_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		if (ops->vidioc_g_fmt_sliced_vbi_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		if (ops->vidioc_g_fmt_sliced_vbi_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_PRIVATE:
		if (ops->vidioc_g_fmt_type_private)
			return 0;
		break;
	}
	return -EINVAL;
}