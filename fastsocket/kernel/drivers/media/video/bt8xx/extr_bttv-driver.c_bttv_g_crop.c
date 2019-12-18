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
struct v4l2_crop {scalar_t__ type; int /*<<< orphan*/  c; } ;
struct file {int dummy; } ;
struct bttv_fh {int /*<<< orphan*/  do_crop; struct bttv* btv; } ;
struct bttv {TYPE_1__* crop; } ;
struct TYPE_2__ {int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 

__attribute__((used)) static int bttv_g_crop(struct file *file, void *f, struct v4l2_crop *crop)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;

	if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    crop->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	/* No fh->do_crop = 1; because btv->crop[1] may be
	   inconsistent with fh->width or fh->height and apps
	   do not expect a change here. */

	crop->c = btv->crop[!!fh->do_crop].rect;

	return 0;
}