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
struct v4l2_buffer {int length; } ;
struct file {int dummy; } ;
struct em28xx_fh {scalar_t__ type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; struct em28xx* dev; } ;
struct em28xx {int vbi_width; int vbi_height; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct em28xx*) ; 
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *priv,
			   struct v4l2_buffer *b)
{
	struct em28xx_fh      *fh  = priv;
	struct em28xx         *dev = fh->dev;
	int                   rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return videobuf_querybuf(&fh->vb_vidq, b);
	else {
		/* FIXME: I'm not sure yet whether this is a bug in zvbi or
		   the videobuf framework, but we probably shouldn't be
		   returning a buffer larger than that which was asked for.
		   At a minimum, it causes a crash in zvbi since it does
		   a memcpy based on the source buffer length */
		int result = videobuf_querybuf(&fh->vb_vbiq, b);
		b->length = dev->vbi_width * dev->vbi_height * 2;

		return result;
	}
}