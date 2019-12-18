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
struct vpfe_device {scalar_t__ memory; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_buffer {scalar_t__ type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vpfe_querybuf(struct file *file, void *priv,
			 struct v4l2_buffer *buf)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_querybuf\n");

	if (V4L2_BUF_TYPE_VIDEO_CAPTURE != buf->type) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		return  -EINVAL;
	}

	if (vpfe_dev->memory != V4L2_MEMORY_MMAP) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid memory\n");
		return -EINVAL;
	}
	/* Call videobuf_querybuf to get information */
	return videobuf_querybuf(&vpfe_dev->buffer_queue, buf);
}