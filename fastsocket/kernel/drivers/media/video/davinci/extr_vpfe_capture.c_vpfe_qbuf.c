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
struct vpfe_fh {int /*<<< orphan*/  io_allowed; } ;
struct vpfe_device {int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_buffer {scalar_t__ type; } ;
struct file {struct vpfe_fh* private_data; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int videobuf_qbuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vpfe_qbuf(struct file *file, void *priv,
		     struct v4l2_buffer *p)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct vpfe_fh *fh = file->private_data;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_qbuf\n");

	if (V4L2_BUF_TYPE_VIDEO_CAPTURE != p->type) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		return -EINVAL;
	}

	/*
	 * If this file handle is not allowed to do IO,
	 * return error
	 */
	if (!fh->io_allowed) {
		v4l2_err(&vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		return -EACCES;
	}
	return videobuf_qbuf(&vpfe_dev->buffer_queue, p);
}