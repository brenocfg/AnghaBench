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
struct pvr2_stream {scalar_t__ buffer_total_count; scalar_t__ buffer_target_count; int /*<<< orphan*/  mutex; } ;
struct pvr2_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_buffer_set_idle (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  pvr2_stream_achieve_buffer_count (struct pvr2_stream*) ; 
 struct pvr2_buffer* pvr2_stream_get_ready_buffer (struct pvr2_stream*) ; 
 int /*<<< orphan*/  pvr2_stream_internal_flush (struct pvr2_stream*) ; 

void pvr2_stream_kill(struct pvr2_stream *sp)
{
	struct pvr2_buffer *bp;
	mutex_lock(&sp->mutex); do {
		pvr2_stream_internal_flush(sp);
		while ((bp = pvr2_stream_get_ready_buffer(sp)) != NULL) {
			pvr2_buffer_set_idle(bp);
		}
		if (sp->buffer_total_count != sp->buffer_target_count) {
			pvr2_stream_achieve_buffer_count(sp);
		}
	} while(0); mutex_unlock(&sp->mutex);
}