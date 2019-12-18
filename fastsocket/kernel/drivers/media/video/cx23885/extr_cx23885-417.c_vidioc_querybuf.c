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
struct v4l2_buffer {int dummy; } ;
struct file {struct cx23885_fh* private_data; } ;
struct cx23885_fh {int /*<<< orphan*/  mpegq; } ;

/* Variables and functions */
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *priv,
				struct v4l2_buffer *p)
{
	struct cx23885_fh  *fh  = file->private_data;

	return videobuf_querybuf(&fh->mpegq, p);
}