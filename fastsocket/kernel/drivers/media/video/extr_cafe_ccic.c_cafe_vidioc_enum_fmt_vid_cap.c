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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t N_CAFE_FMTS ; 
 TYPE_1__* cafe_formats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cafe_vidioc_enum_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_fmtdesc *fmt)
{
	if (fmt->index >= N_CAFE_FMTS)
		return -EINVAL;
	strlcpy(fmt->description, cafe_formats[fmt->index].desc,
			sizeof(fmt->description));
	fmt->pixelformat = cafe_formats[fmt->index].pixelformat;
	return 0;
}