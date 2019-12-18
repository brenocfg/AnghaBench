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
struct ring_buffer {long watermark; int writable; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RING_BUFFER_WRITABLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 long min (long,long) ; 
 long perf_data_size (struct ring_buffer*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ring_buffer_init(struct ring_buffer *rb, long watermark, int flags)
{
	long max_size = perf_data_size(rb);

	if (watermark)
		rb->watermark = min(max_size, watermark);

	if (!rb->watermark)
		rb->watermark = max_size / 2;

	if (flags & RING_BUFFER_WRITABLE)
		rb->writable = 1;

	atomic_set(&rb->refcount, 1);

	INIT_LIST_HEAD(&rb->event_list);
	spin_lock_init(&rb->event_lock);
}