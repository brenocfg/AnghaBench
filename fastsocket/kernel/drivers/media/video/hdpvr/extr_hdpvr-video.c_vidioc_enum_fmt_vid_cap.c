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
struct v4l2_fmtdesc {scalar_t__ index; scalar_t__ type; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void *private_data,
				    struct v4l2_fmtdesc *f)
{

	if (f->index != 0 || f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	f->flags = V4L2_FMT_FLAG_COMPRESSED;
	strncpy(f->description, "MPEG2-TS with AVC/AAC streams", 32);
	f->pixelformat = V4L2_PIX_FMT_MPEG;

	return 0;
}