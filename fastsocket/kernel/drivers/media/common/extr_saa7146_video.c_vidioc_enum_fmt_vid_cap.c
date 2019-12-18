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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; scalar_t__ description; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_FORMATS ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
	if (f->index >= NUM_FORMATS)
		return -EINVAL;
	strlcpy((char *)f->description, formats[f->index].name,
			sizeof(f->description));
	f->pixelformat = formats[f->index].pixelformat;
	return 0;
}