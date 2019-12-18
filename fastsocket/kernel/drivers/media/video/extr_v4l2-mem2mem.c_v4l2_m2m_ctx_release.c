#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct videobuf_buffer {scalar_t__ state; int /*<<< orphan*/  done; } ;
struct v4l2_m2m_dev {int /*<<< orphan*/  job_spinlock; TYPE_1__* m2m_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  q; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct v4l2_m2m_ctx {int job_flags; TYPE_3__ out_q_ctx; TYPE_2__ cap_q_ctx; int /*<<< orphan*/  queue; int /*<<< orphan*/  priv; struct v4l2_m2m_dev* m2m_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* job_abort ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int TRANS_QUEUED ; 
 int TRANS_RUNNING ; 
 scalar_t__ VIDEOBUF_ACTIVE ; 
 scalar_t__ VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  dprintk (char*,struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  kfree (struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct videobuf_buffer* v4l2_m2m_next_dst_buf (struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void v4l2_m2m_ctx_release(struct v4l2_m2m_ctx *m2m_ctx)
{
	struct v4l2_m2m_dev *m2m_dev;
	struct videobuf_buffer *vb;
	unsigned long flags;

	m2m_dev = m2m_ctx->m2m_dev;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	if (m2m_ctx->job_flags & TRANS_RUNNING) {
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		m2m_dev->m2m_ops->job_abort(m2m_ctx->priv);
		dprintk("m2m_ctx %p running, will wait to complete", m2m_ctx);
		vb = v4l2_m2m_next_dst_buf(m2m_ctx);
		BUG_ON(NULL == vb);
		wait_event(vb->done, vb->state != VIDEOBUF_ACTIVE
				     && vb->state != VIDEOBUF_QUEUED);
	} else if (m2m_ctx->job_flags & TRANS_QUEUED) {
		list_del(&m2m_ctx->queue);
		m2m_ctx->job_flags &= ~(TRANS_QUEUED | TRANS_RUNNING);
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprintk("m2m_ctx: %p had been on queue and was removed\n",
			m2m_ctx);
	} else {
		/* Do nothing, was not on queue/running */
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
	}

	videobuf_stop(&m2m_ctx->cap_q_ctx.q);
	videobuf_stop(&m2m_ctx->out_q_ctx.q);

	videobuf_mmap_free(&m2m_ctx->cap_q_ctx.q);
	videobuf_mmap_free(&m2m_ctx->out_q_ctx.q);

	kfree(m2m_ctx);
}