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
struct v4l2_m2m_queue_ctx {struct videobuf_queue q; } ;
struct v4l2_m2m_ctx {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 struct v4l2_m2m_queue_ctx* get_queue_ctx (struct v4l2_m2m_ctx*,int) ; 

struct videobuf_queue *v4l2_m2m_get_vq(struct v4l2_m2m_ctx *m2m_ctx,
				       enum v4l2_buf_type type)
{
	struct v4l2_m2m_queue_ctx *q_ctx;

	q_ctx = get_queue_ctx(m2m_ctx, type);
	if (!q_ctx)
		return NULL;

	return &q_ctx->q;
}