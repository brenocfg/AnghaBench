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
struct pvr2_stream_stats {scalar_t__ bytes_processed; scalar_t__ buffers_failed; scalar_t__ buffers_processed; int /*<<< orphan*/  buffers_in_ready; int /*<<< orphan*/  buffers_in_idle; int /*<<< orphan*/  buffers_in_queue; } ;
struct pvr2_stream {int /*<<< orphan*/  list_lock; scalar_t__ bytes_processed; scalar_t__ buffers_failed; scalar_t__ buffers_processed; int /*<<< orphan*/  r_count; int /*<<< orphan*/  i_count; int /*<<< orphan*/  q_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pvr2_stream_get_stats(struct pvr2_stream *sp,
			   struct pvr2_stream_stats *stats,
			   int zero_counts)
{
	unsigned long irq_flags;
	spin_lock_irqsave(&sp->list_lock,irq_flags);
	if (stats) {
		stats->buffers_in_queue = sp->q_count;
		stats->buffers_in_idle = sp->i_count;
		stats->buffers_in_ready = sp->r_count;
		stats->buffers_processed = sp->buffers_processed;
		stats->buffers_failed = sp->buffers_failed;
		stats->bytes_processed = sp->bytes_processed;
	}
	if (zero_counts) {
		sp->buffers_processed = 0;
		sp->buffers_failed = 0;
		sp->bytes_processed = 0;
	}
	spin_unlock_irqrestore(&sp->list_lock,irq_flags);
}