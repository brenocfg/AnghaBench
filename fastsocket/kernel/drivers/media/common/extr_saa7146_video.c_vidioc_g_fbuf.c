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
struct v4l2_framebuffer {int /*<<< orphan*/  capability; } ;
struct saa7146_vv {struct v4l2_framebuffer ov_fb; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FBUF_CAP_LIST_CLIPPING ; 

__attribute__((used)) static int vidioc_g_fbuf(struct file *file, void *fh, struct v4l2_framebuffer *fb)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct saa7146_vv *vv = dev->vv_data;

	*fb = vv->ov_fb;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	return 0;
}