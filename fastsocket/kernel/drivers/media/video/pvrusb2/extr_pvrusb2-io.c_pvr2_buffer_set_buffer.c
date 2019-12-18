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
struct pvr2_stream {unsigned int i_bcount; int /*<<< orphan*/  mutex; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  i_count; } ;
struct pvr2_buffer {scalar_t__ state; unsigned int max_count; struct pvr2_stream* stream; void* ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  PVR2_TRACE_BUF_FLOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_buffer_state_decode (scalar_t__) ; 
 scalar_t__ pvr2_buffer_state_idle ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pvr2_buffer_set_buffer(struct pvr2_buffer *bp,void *ptr,unsigned int cnt)
{
	int ret = 0;
	unsigned long irq_flags;
	struct pvr2_stream *sp;
	if (!bp) return -EINVAL;
	sp = bp->stream;
	mutex_lock(&sp->mutex); do {
		spin_lock_irqsave(&sp->list_lock,irq_flags);
		if (bp->state != pvr2_buffer_state_idle) {
			ret = -EPERM;
		} else {
			bp->ptr = ptr;
			bp->stream->i_bcount -= bp->max_count;
			bp->max_count = cnt;
			bp->stream->i_bcount += bp->max_count;
			pvr2_trace(PVR2_TRACE_BUF_FLOW,
				   "/*---TRACE_FLOW---*/ bufferPool    "
				   " %8s cap cap=%07d cnt=%02d",
				   pvr2_buffer_state_decode(
					   pvr2_buffer_state_idle),
				   bp->stream->i_bcount,bp->stream->i_count);
		}
		spin_unlock_irqrestore(&sp->list_lock,irq_flags);
	} while(0); mutex_unlock(&sp->mutex);
	return ret;
}