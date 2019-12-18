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
struct v4l2_fmtdesc {scalar_t__ index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zr364xx_vidioc_enum_fmt_vid_cap(struct file *file,
				       void *priv, struct v4l2_fmtdesc *f)
{
	if (f->index > 0)
		return -EINVAL;
	f->flags = V4L2_FMT_FLAG_COMPRESSED;
	strcpy(f->description, formats[0].name);
	f->pixelformat = formats[0].fourcc;
	return 0;
}