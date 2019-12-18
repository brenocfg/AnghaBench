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
struct pvr2_stream {int /*<<< orphan*/  list_lock; struct pvr2_buffer* q_count; struct pvr2_buffer* q_bcount; int /*<<< orphan*/  queued_list; } ;
struct pvr2_buffer {int /*<<< orphan*/  state; scalar_t__ max_count; int /*<<< orphan*/  list_overhead; struct pvr2_stream* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_CHECK (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  PVR2_TRACE_BUF_FLOW ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_buffer_remove (struct pvr2_buffer*) ; 
 struct pvr2_buffer* pvr2_buffer_state_decode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_buffer_state_queued ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_buffer*,struct pvr2_buffer*,struct pvr2_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pvr2_buffer_set_queued(struct pvr2_buffer *bp)
{
	unsigned long irq_flags;
	struct pvr2_stream *sp;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferState    %p %6s --> %6s",
		   bp,
		   pvr2_buffer_state_decode(bp->state),
		   pvr2_buffer_state_decode(pvr2_buffer_state_queued));
	spin_lock_irqsave(&sp->list_lock,irq_flags);
	pvr2_buffer_remove(bp);
	list_add_tail(&bp->list_overhead,&sp->queued_list);
	bp->state = pvr2_buffer_state_queued;
	(sp->q_count)++;
	sp->q_bcount += bp->max_count;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/"
		   " bufferPool     %8s inc cap=%07d cnt=%02d",
		   pvr2_buffer_state_decode(bp->state),
		   sp->q_bcount,sp->q_count);
	spin_unlock_irqrestore(&sp->list_lock,irq_flags);
}