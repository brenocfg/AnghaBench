#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_m2m_dev {int /*<<< orphan*/  job_spinlock; int /*<<< orphan*/  job_queue; TYPE_5__* m2m_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/ * irqlock; int /*<<< orphan*/  streaming; } ;
struct TYPE_9__ {TYPE_3__ q; int /*<<< orphan*/  rdy_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  streaming; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdy_queue; TYPE_1__ q; } ;
struct v4l2_m2m_ctx {int job_flags; int /*<<< orphan*/  queue; int /*<<< orphan*/  priv; TYPE_4__ out_q_ctx; TYPE_2__ cap_q_ctx; struct v4l2_m2m_dev* m2m_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* job_ready ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int TRANS_QUEUED ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_try_run (struct v4l2_m2m_dev*) ; 

__attribute__((used)) static void v4l2_m2m_try_schedule(struct v4l2_m2m_ctx *m2m_ctx)
{
	struct v4l2_m2m_dev *m2m_dev;
	unsigned long flags_job, flags;

	m2m_dev = m2m_ctx->m2m_dev;
	dprintk("Trying to schedule a job for m2m_ctx: %p\n", m2m_ctx);

	if (!m2m_ctx->out_q_ctx.q.streaming
	    || !m2m_ctx->cap_q_ctx.q.streaming) {
		dprintk("Streaming needs to be on for both queues\n");
		return;
	}

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags_job);
	if (m2m_ctx->job_flags & TRANS_QUEUED) {
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);
		dprintk("On job queue already\n");
		return;
	}

	spin_lock_irqsave(m2m_ctx->out_q_ctx.q.irqlock, flags);
	if (list_empty(&m2m_ctx->out_q_ctx.rdy_queue)) {
		spin_unlock_irqrestore(m2m_ctx->out_q_ctx.q.irqlock, flags);
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);
		dprintk("No input buffers available\n");
		return;
	}
	if (list_empty(&m2m_ctx->cap_q_ctx.rdy_queue)) {
		spin_unlock_irqrestore(m2m_ctx->out_q_ctx.q.irqlock, flags);
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);
		dprintk("No output buffers available\n");
		return;
	}
	spin_unlock_irqrestore(m2m_ctx->out_q_ctx.q.irqlock, flags);

	if (m2m_dev->m2m_ops->job_ready
		&& (!m2m_dev->m2m_ops->job_ready(m2m_ctx->priv))) {
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);
		dprintk("Driver not ready\n");
		return;
	}

	list_add_tail(&m2m_ctx->queue, &m2m_dev->job_queue);
	m2m_ctx->job_flags |= TRANS_QUEUED;

	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);

	v4l2_m2m_try_run(m2m_dev);
}