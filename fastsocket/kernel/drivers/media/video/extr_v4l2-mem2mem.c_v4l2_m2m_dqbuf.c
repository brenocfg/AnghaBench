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
struct videobuf_queue {int dummy; } ;
struct v4l2_m2m_ctx {int dummy; } ;
struct v4l2_buffer {int /*<<< orphan*/  type; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 struct videobuf_queue* v4l2_m2m_get_vq (struct v4l2_m2m_ctx*,int /*<<< orphan*/ ) ; 
 int videobuf_dqbuf (struct videobuf_queue*,struct v4l2_buffer*,int) ; 

int v4l2_m2m_dqbuf(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
		   struct v4l2_buffer *buf)
{
	struct videobuf_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	return videobuf_dqbuf(vq, buf, file->f_flags & O_NONBLOCK);
}