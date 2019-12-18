#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; int /*<<< orphan*/  capability; } ;
struct file {int dummy; } ;
struct bttv_fh {TYPE_2__* ovfmt; struct bttv* btv; } ;
struct bttv {struct v4l2_framebuffer fbuf; } ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FBUF_CAP_LIST_CLIPPING ; 

__attribute__((used)) static int bttv_g_fbuf(struct file *file, void *f,
				struct v4l2_framebuffer *fb)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;

	*fb = btv->fbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	if (fh->ovfmt)
		fb->fmt.pixelformat  = fh->ovfmt->fourcc;
	return 0;
}