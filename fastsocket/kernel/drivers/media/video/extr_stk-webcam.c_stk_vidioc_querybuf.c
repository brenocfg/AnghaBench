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
struct v4l2_buffer {scalar_t__ index; } ;
struct stk_sio_buffer {struct v4l2_buffer v4lbuf; } ;
struct stk_camera {scalar_t__ n_sbufs; struct stk_sio_buffer* sio_bufs; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int stk_vidioc_querybuf(struct file *filp,
		void *priv, struct v4l2_buffer *buf)
{
	struct stk_camera *dev = priv;
	struct stk_sio_buffer *sbuf;

	if (buf->index >= dev->n_sbufs)
		return -EINVAL;
	sbuf = dev->sio_bufs + buf->index;
	*buf = sbuf->v4lbuf;
	return 0;
}