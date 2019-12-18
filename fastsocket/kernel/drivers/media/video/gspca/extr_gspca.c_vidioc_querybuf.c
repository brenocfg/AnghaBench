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
struct v4l2_buffer {size_t index; } ;
struct gspca_frame {int /*<<< orphan*/  v4l2_buf; } ;
struct gspca_dev {size_t nframes; struct gspca_frame* frame; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct v4l2_buffer*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *priv,
			   struct v4l2_buffer *v4l2_buf)
{
	struct gspca_dev *gspca_dev = priv;
	struct gspca_frame *frame;

	if (v4l2_buf->index < 0
	    || v4l2_buf->index >= gspca_dev->nframes)
		return -EINVAL;

	frame = &gspca_dev->frame[v4l2_buf->index];
	memcpy(v4l2_buf, &frame->v4l2_buf, sizeof *v4l2_buf);
	return 0;
}